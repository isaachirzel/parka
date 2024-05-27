#ifndef PARKA_UTIL_BINARY_OPERATOR_UTIL_HPP
#define PARKA_UTIL_BINARY_OPERATOR_UTIL_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/util/TypeUtil.hpp"

namespace parka
{
	template <BinaryExpressionType binaryExpressionType, typename Left, typename Right = Left, typename Return = Left>
	ir::BinaryOperatorIr& binop()
	{
		static ir::BinaryOperatorIr op(binaryExpressionType, type<Left>(), type<Right>(), type<Return>());

		return op;
	}
}

#endif
