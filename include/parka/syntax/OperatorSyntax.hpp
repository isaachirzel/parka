#ifndef PARKA_SYNTAX_FUNCTION_OPERATOR_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_OPERATOR_SYNTAX_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class Operator
	{
		ValueType _leftType;
		ValueType _rightType;
		ExpressionSyntax *_body;
		OperatorType _type;

	public:

		Operator(ValueType&& leftType, ValueType&& rightType, ExpressionSyntax *body, OperatorType type) :
		_leftType(std::move(leftType)),
		_rightType(std::move(rightType)),
		_body(body),
		_type(type)
		{}

		static Optional<Operator> parse(Token& token);

		const auto& leftType() const { return _leftType; }
		const auto& rightType() const { return _rightType; }
		const auto& body() const { return _body; }
		const auto& type() const { return _type; }
	};
}

#endif
