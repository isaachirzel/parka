#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/type.hpp"
#include "parka/util/box.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/ref.hpp"

class SymbolTable;

struct Expression
{
	static Optional<Box<Expression>> parse(Token& token);

	virtual ~Expression() {}
	virtual bool validate(SymbolTable& symbols) = 0;
	virtual Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const = 0;
	// TODO: virtual Token getToken() const = 0;
};

#endif
