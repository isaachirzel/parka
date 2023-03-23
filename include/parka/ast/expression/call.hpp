#ifndef PARKA_AST_EXPRESSION_CALL_HPP
#define PARKA_AST_EXPRESSION_CALL_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"

class CallExpression : public Expression
{
	Array<Box<Expression>> _arguments;

	CallExpression(Array<Box<Expression>>&& arguments) :
	_arguments(std::move(arguments))
	{}

public:

	CallExpression(CallExpression&&) = default;
	CallExpression(const CallExpression&) = delete;
	~CallExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& arguments() const { return _arguments; }
};

#endif
