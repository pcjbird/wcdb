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

#ifndef Reporter_hpp
#define Reporter_hpp

#include <WCDB/Error.hpp>
#include <WCDB/Lock.hpp>

namespace WCDB {

class Notifier {
public:
    typedef std::function<void(const Error &)> Callback;
    static Notifier *shared();

    void notify(const Error &error) const;

    void setNotification(const Callback &callback);

protected:
    mutable SharedLock m_lock;

    Callback m_callback;

public:
    static void fatal(const std::string &message, const char *file, int line);
    static void error(const std::string &message, const char *file, int line);
    static void warning(const std::string &message, const char *file, int line);

protected:
    static void
    error(Error::Level level, const std::string &message, const char *file, int line);
};

} //namespace WCDB

#endif /* Reporter_hpp */