#ifndef PARKA_AST_EXRPESSION_BLOCK_HPP
#define PARKA_AST_EXRPESSION_BLOCK_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/type.hpp"
#include "parka/util/primitives.hpp"

struct Block : public Expression
{
	Array<Box<Statement>> _statements;
	Optional<Type> _returnType;

	Block(Array<Box<Statement>>&& statements, Optional<Type>&& returnType = {}) :
	_statements(std::move(statements)),
	_returnType(std::move(returnType))
	{}

public:

	Block(Block&&) = default;
	Block(const Block&) = delete;
	~Block() = default;;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& statements() const { return _statements; }
};

#endif
