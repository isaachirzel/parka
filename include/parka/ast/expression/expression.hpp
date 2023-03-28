#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/ast/module.hpp"
#include "parka/symbol/expression_id.hpp"
#include "parka/token.hpp"
#include "parka/type.hpp"
#include "parka/util/box.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/ref.hpp"
#include "parka/symbol/symbol_table.hpp"

struct Expression
{
	static Optional<ExpressionId> parse(Token& token);

	virtual ~Expression() {}

	virtual bool validate(SymbolTable& symbols) = 0;
	virtual Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const = 0;
};

#endif
