#ifndef PARKA_AST_EXRPESSION_BLOCK_HPP
#define PARKA_AST_EXRPESSION_BLOCK_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/util/primitives.hpp"

class Block : public Expression
{
	Array<StatementId> _statements;
	Optional<Type> _returnType;

	Block(Array<StatementId>&& statements, Optional<Type>&& returnType = {}) :
	_statements(std::move(statements)),
	_returnType(std::move(returnType))
	{}

public:

	Block(Block&&) = default;
	Block(const Block&) = delete;
	~Block() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& statements() const { return _statements; }
};

#endif