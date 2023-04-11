#ifndef PARKA_SYNTAX_FUNCTION_OPERATOR_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_OPERATOR_SYNTAX_HPP

#include "parka/data/ExpressionId.hpp"
#include "parka/syntax/OperatorId.hpp"
#include "parka/type/Type.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class Operator
	{
		Type _leftType;
		Type _rightType;
		Optional<ExpressionId> _body;
		OperatorType _type;

	public:

		Operator(Type&& leftType, Type&& rightType, Optional<ExpressionId>&& body, OperatorType type) :
		_leftType(std::move(leftType)),
		_rightType(std::move(rightType)),
		_body(std::move(body)),
		_type(type)
		{}

		static Optional<Operator> parse(Token& token);

		bool validate(const EntityId& functionId);

		const auto& leftType() const { return _leftType; }
		const auto& rightType() const { return _rightType; }
		const auto& body() const { return _body; }
		const auto& type() const { return _type; }
	};
}

#endif
