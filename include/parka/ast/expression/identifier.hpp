#ifndef PARKA_AST_EXPRESSION_IDENTIFIER_HPP
#define PARKA_AST_EXPRESSION_IDENTIFIER_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/token.hpp"
#include "parka/type.hpp"
#include "parka/util/optional.hpp"

class Identifier : public Expression
{
	Token _token;
	Optional<EntityId> _entityId;

	Identifier(const Token & token) :
	_token(token)
	{}

public:

	Identifier(Identifier&&) = default;
	Identifier(const Identifier&) = delete;
	~Identifier() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(SymbolTable& symbols);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& token() const { return _token; }
	const auto& entityId() const { return _entityId; }
};

#endif
