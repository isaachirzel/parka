#ifndef PARKA_ENUM_OPERATOR_TYPE_HPP
#define PARKA_ENUM_OPERATOR_TYPE_HPP

#include "parka/enum/BinaryExpressionType.hpp"
namespace parka
{
	enum class OperatorType
	{
		Add,
		Subtract,
		Multiply,
		Divide
	};

	OperatorType toOperatorType(BinaryExpressionType type);
	std::ostream& operator<<(std::ostream& out, const OperatorType& type);
}

#endif
