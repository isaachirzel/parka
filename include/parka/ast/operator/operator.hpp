#ifndef PARKA_AST_FUNCTION_OPERATOR_HPP
#define PARKA_AST_FUNCTION_OPERATOR_HPP

#include "parka/symbol/expression_id.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/ast/operator/operator_id.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/util/optional.hpp"

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

	bool validate(LocalSymbolTable& symbols);

	const auto& leftType() const { return _leftType; }
	const auto& rightType() const { return _rightType; }
	const auto& body() const { return _body; }
	const auto& type() const { return _type; }
};

#endif
