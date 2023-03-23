#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/type.hpp"
#include "parka/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class TypeAnnotation
{
	Token _token;
	Type _type;

	TypeAnnotation(const Token& token, Type&& type) :
	_token(token),
	_type(std::move(type))
	{}

public:

	TypeAnnotation(TypeAnnotation&&) = default;
	TypeAnnotation(const TypeAnnotation&) = delete;
	~TypeAnnotation() = default;

	static Optional<TypeAnnotation> parse(Token& token);

	bool validate(const Scope& packageScope);

	const auto& token() const { return _token; }
	const auto& type() const { return _type; }
};

#endif
