/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <WCDB/FileManager.hpp>
#include <WCDB/Path.hpp>
#include <WCDB/String.hpp>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

namespace WCDB {

FileError::FileError() : Error(), operation(Operation::NotSet)
{
}

std::string FileError::getDescription() const
{
    std::string description = Error::getDescription();
    addToDescription(description, "Op", operation);
    addToDescription(description, "Path", path);
    return description;
}

size_t FileError::getHashedTypeid() const
{
    return typeid(FileError).hash_code();
}

FileManager::FileManager()
{
}

FileManager *FileManager::shared()
{
    static FileManager s_fileManager;
    return &s_fileManager;
}

#pragma mark - Basic
std::pair<bool, size_t> FileManager::getFileSize(const std::string &path)
{
    struct stat temp;
    if (lstat(path.c_str(), &temp) == 0) {
        return {true, (size_t) temp.st_size};
    } else if (errno == ENOENT) {
        return {true, 0};
    }
    setupAndReportError(FileError::Operation::Lstat, path);
    return {false, 0};
}

std::pair<bool, bool> FileManager::isExists(const std::string &path)
{
    if (access(path.c_str(), F_OK) == 0) {
        return {true, true};
    } else if (errno == ENOENT) {
        return {true, false};
    }
    setupAndReportError(FileError::Operation::Access, path);
    return {false, false};
}

bool FileManager::createHardLink(const std::string &from, const std::string &to)
{
    if (link(from.c_str(), to.c_str()) == 0) {
        return true;
    }
    setupAndReportError(FileError::Operation::Link, to);
    return false;
}

bool FileManager::removeHardLink(const std::string &path)
{
    if (unlink(path.c_str()) == 0 || errno == ENOENT) {
        return true;
    }
    setupAndReportError(FileError::Operation::Unlink, path);
    return false;
}

bool FileManager::removeFile(const std::string &path)
{
    if (remove(path.c_str()) == 0 || errno == ENOENT) {
        return true;
    }
    setupAndReportError(FileError::Operation::Remove, path);
    return false;
}

bool FileManager::createDirectory(const std::string &path)
{
    if (mkdir(path.c_str(), 0755) == 0) {
        return true;
    }
    setupAndReportError(FileError::Operation::Mkdir, path);
    return false;
}

#pragma mark - Combination
std::pair<bool, size_t>
FileManager::getFilesSize(const std::list<std::string> &paths)
{
    size_t size = 0;
    std::pair<bool, size_t> ret;
    for (const auto &path : paths) {
        ret = getFileSize(path);
        if (ret.first) {
            size += ret.second;
        } else {
            return {false, 0};
        }
    }
    return {true, size};
}

bool FileManager::moveFiles(const std::list<std::string> &paths,
                            const std::string &directory)
{
    if (!createDirectoryWithIntermediateDirectories(directory)) {
        return false;
    }
    bool result = true;
    std::list<std::string> recovers;
    for (const auto &path : paths) {
        std::pair<bool, bool> ret = isExists(path);
        if (!ret.first) {
            break;
        }
        if (ret.second) {
            const std::string fileName = Path::getFileName(path);
            std::string newPath = Path::addComponent(directory, fileName);
            if (!removeFile(newPath) || !createHardLink(path, newPath)) {
                result = false;
                break;
            }
            recovers.push_back(newPath);
        }
    }
    if (result) {
        removeFiles(paths);
    } else {
        for (const auto &recover : recovers) {
            removeHardLink(recover.c_str());
        }
    }
    return result;
}

bool FileManager::removeFiles(const std::list<std::string> &paths)
{
    for (const auto &path : paths) {
        if (!removeFile(path)) {
            return false;
        }
    }
    return true;
}

bool FileManager::createDirectoryWithIntermediateDirectories(
    const std::string &path)
{
    auto ret = isExists(path);
    if (!ret.first) {
        return false;
    }
    if (!ret.second) {
        return createDirectoryWithIntermediateDirectories(
                   Path::getBaseName(path)) &&
               createDirectory(path);
    }
    return true;
}

#pragma mark - Error
void FileManager::setupAndReportError(FileError::Operation operation,
                                      const std::string &path)
{
    FileError *error = m_errors.get();
    error->code = errno;
    error->operation = operation;
    error->path = path;
    error->message = strerror(errno);
    error->report();
}

const FileError &FileManager::getError()
{
    return *m_errors.get();
}

} //namespace WCDB