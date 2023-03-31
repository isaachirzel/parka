#ifndef PARKA_AST_EXPRESSION_INDEX_HPP
#define PARKA_AST_EXPRESSION_INDEX_HPP

#include "parka/ast/expression/expression.hpp"

#include <utility>

class IndexExpression : public Expression
{
	ExpressionId _primary;
	ExpressionId _index;

	IndexExpression(ExpressionId primary, ExpressionId index) :
	_primary(primary),
	_index(index)
	{}

public:

	static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& expression() const { return _primary; }
	const auto& index() const { return _index; }
};

#endif
