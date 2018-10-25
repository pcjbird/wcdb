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

#include <WCDB/WINQ.h>

namespace WCDB {

Expression CoreFunction::abs(const Expression& expression)
{
    return Expression::function("abs").invoke(expression);
}

Expression CoreFunction::changes()
{
    return Expression::function("changes").invoke();
}

Expression CoreFunction::char_(const Expressions& expressions)
{
    return Expression::function("char").invoke(expressions);
}

Expression CoreFunction::coalesce(const Expressions& expressions)
{
    return Expression::function("coalesce").invoke(expressions);
}

Expression CoreFunction::glob(const Expression& pattern, const Expression& string)
{
    return Expression::function("glob").invoke({ pattern, string });
}

Expression CoreFunction::hex(const Expression& expression)
{
    return Expression::function("hex").invoke(expression);
}

Expression CoreFunction::ifNull(const Expression& expression1, const Expression& expression2)
{
    return Expression::function("ifnull").invoke({ expression1, expression2 });
}

Expression CoreFunction::instr(const Expression& string, const Expression& occurrence)
{
    return Expression::function("instr").invoke({ string, occurrence });
}

Expression CoreFunction::lastInsertRowID()
{
    return Expression::function("last_insert_rowid").invoke();
}

Expression CoreFunction::length(const Expression& expression)
{
    return Expression::function("length").invoke(expression);
}

Expression CoreFunction::like(const Expression& origin, const Expression& pattern)
{
    return Expression::function("like").invoke({ origin, pattern });
}

Expression
CoreFunction::like(const Expression& origin, const Expression& pattern, const Expression& escape)
{
    return Expression::function("like").invoke({ origin, pattern, escape });
}

Expression CoreFunction::likelihood(const Expression& unchanged, const Expression& floating)
{
    return Expression::function("likelihood").invoke({ unchanged, floating });
}

Expression CoreFunction::likely(const Expression& unchanged)
{
    return Expression::function("likely").invoke(unchanged);
}

Expression CoreFunction::lower(const Expression& expression)
{
    return Expression::function("lower").invoke(expression);
}

Expression CoreFunction::ltrim(const Expression& expression)
{
    return Expression::function("ltrim").invoke(expression);
}

Expression CoreFunction::ltrim(const Expression& expression, const Expression& removing)
{
    return Expression::function("ltrim").invoke({ expression, removing });
}

Expression CoreFunction::max(const Expressions& expressions)
{
    return Expression::function("max").invoke(expressions);
}

Expression CoreFunction::min(const Expressions& expressions)
{
    return Expression::function("min").invoke(expressions);
}

Expression CoreFunction::nullIf(const Expression& expression1, const Expression& expression2)
{
    return Expression::function("nullif").invoke({ expression1, expression2 });
}

Expression CoreFunction::printf(const Expressions& expressions)
{
    return Expression::function("printf").invoke(expressions);
}

Expression CoreFunction::quote(const Expression& expression)
{
    return Expression::function("quote").invoke(expression);
}

Expression CoreFunction::random()
{
    return Expression::function("random").invoke();
}

Expression CoreFunction::randomBLOB(const Expression& n)
{
    return Expression::function("randomblob").invoke(n);
}

Expression CoreFunction::replace(const Expression& origin,
                                 const Expression& target,
                                 const Expression& replacement)
{
    return Expression::function("replace").invoke({ origin, target, replacement });
}

Expression CoreFunction::round(const Expression& expression)
{
    return Expression::function("round").invoke(expression);
}

Expression CoreFunction::round(const Expression& expression, const Expression& digits)
{
    return Expression::function("round").invoke({ expression, digits });
}

Expression CoreFunction::rtrim(const Expression& expression)
{
    return Expression::function("rtrim").invoke(expression);
}

Expression CoreFunction::rtrim(const Expression& expression, const Expression& removing)
{
    return Expression::function("rtrim").invoke({ expression, removing });
}

Expression CoreFunction::soundex(const Expression& expression)
{
    return Expression::function("soundex").invoke(expression);
}

Expression CoreFunction::sqliteCompileOptionGet(const Expression& n)
{
    return Expression::function("sqlite_compileoption_get").invoke(n);
}

Expression CoreFunction::sqliteCompileOptionUsed(const Expression& name)
{
    return Expression::function("sqlite_compileoption_used").invoke(name);
}

Expression CoreFunction::sqliteOffset(const Expression& expression)
{
    return Expression::function("sqlite_offset").invoke(expression);
}

Expression CoreFunction::sqliteSourceID()
{
    return Expression::function("sqlite_source_id").invoke();
}

Expression CoreFunction::sqliteVersion()
{
    return Expression::function("sqlite_version").invoke();
}

Expression CoreFunction::substr(const Expression& origin, const Expression& offset)
{
    return Expression::function("substr").invoke({ origin, offset });
}

Expression
CoreFunction::substr(const Expression& origin, const Expression& offset, const Expression& length)
{
    return Expression::function("substr").invoke({ origin, offset, length });
}

Expression CoreFunction::totalChanges()
{
    return Expression::function("total_changes").invoke();
}

Expression CoreFunction::trim(const Expression& expression)
{
    return Expression::function("trim").invoke(expression);
}

Expression CoreFunction::trim(const Expression& expression, const Expression& removing)
{
    return Expression::function("trim").invoke({ expression, removing });
}

Expression CoreFunction::typeof_(const Expression& expression)
{
    return Expression::function("typeof").invoke(expression);
}

Expression CoreFunction::unicode(const Expression& expression)
{
    return Expression::function("unicode").invoke(expression);
}

Expression CoreFunction::unlikely(const Expression& expression)
{
    return Expression::function("unlikely").invoke(expression);
}

Expression CoreFunction::upper(const Expression& expression)
{
    return Expression::function("upper").invoke(expression);
}

Expression CoreFunction::zeroBLOB(const Expression& expression)
{
    return Expression::function("zeroblob").invoke(expression);
}

CoreFunctionOperable::~CoreFunctionOperable()
{
}

Expression CoreFunctionOperable::abs() const
{
    return CoreFunction::abs(asExpressionOperand());
}

Expression CoreFunctionOperable::hex() const
{
    return CoreFunction::hex(asExpressionOperand());
}

Expression CoreFunctionOperable::length() const
{
    return CoreFunction::length(asExpressionOperand());
}

Expression CoreFunctionOperable::lower() const
{
    return CoreFunction::lower(asExpressionOperand());
}

Expression CoreFunctionOperable::ltrim() const
{
    return CoreFunction::ltrim(asExpressionOperand());
}

Expression CoreFunctionOperable::ltrim(const Expression& removing) const
{
    return CoreFunction::ltrim(asExpressionOperand(), removing);
}

Expression CoreFunctionOperable::replace(const Expression& pattern,
                                         const Expression& replacement) const
{
    return CoreFunction::replace(asExpressionOperand(), pattern, replacement);
}

Expression CoreFunctionOperable::round() const
{
    return CoreFunction::round(asExpressionOperand());
}

Expression CoreFunctionOperable::round(const Expression& digits) const
{
    return CoreFunction::round(asExpressionOperand(), digits);
}

Expression CoreFunctionOperable::rtrim() const
{
    return CoreFunction::rtrim(asExpressionOperand());
}

Expression CoreFunctionOperable::rtrim(const Expression& removing) const
{
    return CoreFunction::rtrim(asExpressionOperand(), removing);
}

Expression CoreFunctionOperable::substr(const Expression& offset) const
{
    return CoreFunction::substr(asExpressionOperand(), offset);
}

Expression
CoreFunctionOperable::substr(const Expression& offset, const Expression& length) const
{
    return CoreFunction::substr(asExpressionOperand(), offset, length);
}

Expression CoreFunctionOperable::trim() const
{
    return CoreFunction::trim(asExpressionOperand());
}

Expression CoreFunctionOperable::trim(const Expression& removing) const
{
    return CoreFunction::trim(asExpressionOperand(), removing);
}

Expression CoreFunctionOperable::typeof_() const
{
    return CoreFunction::typeof_(asExpressionOperand());
}

Expression CoreFunctionOperable::upper() const
{
    return CoreFunction::upper(asExpressionOperand());
}

} // namespace WCDB