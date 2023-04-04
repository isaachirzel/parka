#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/ast/qualified_identifier.hpp"
#include "parka/symbol/expression_id.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class TypeAnnotation
{
	QualifiedIdentifier _identifier;
	// // TODO: Add type after validation
	Optional<Type> _type; // Having an optional type is causing this a free warning to come up

	TypeAnnotation(QualifiedIdentifier&& identifier) :
	_identifier(std::move(identifier)),
	_type()
	{}

public:

	TypeAnnotation(TypeAnnotation&&) = default;
	TypeAnnotation(const TypeAnnotation&) = delete;
	~TypeAnnotation() = default;

	static Optional<TypeAnnotation> parse(Token& token);

	bool validate(const EntityId& functionId);

	const auto& identifier() const { return _identifier; }
	const Type& type() const { throw std::exception(); }
};

#endif
