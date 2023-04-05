#ifndef PARKA_AST_EXPRESSION_IDENTIFIER_HPP
#define PARKA_AST_EXPRESSION_IDENTIFIER_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/qualified_identifier.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/token.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/util/optional.hpp"

class IdentifierExpression : public Expression
{
	QualifiedIdentifier _identifier;
	Optional<EntityId> _entityId;

	IdentifierExpression(QualifiedIdentifier&& identifier) :
	_identifier(std::move(identifier)),
	_entityId()
	{}

public:

	IdentifierExpression(IdentifierExpression&&) = default;
	IdentifierExpression(const IdentifierExpression&) = delete;
	~IdentifierExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;
	
	const auto& identifier() const { return _identifier; }
};

#endif
