#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/symbol/symbol_table.hpp"
#include "parka/type.hpp"
#include "parka/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class TypeAnnotation
{
	Token _token;
	// TODO: Add type after validation
	Optional<Type> _type; 

	TypeAnnotation(const Token& token) :
	_token(token)
	{}

public:

	TypeAnnotation(TypeAnnotation&&) = default;
	TypeAnnotation(const TypeAnnotation&) = delete;
	~TypeAnnotation() = default;

	static Optional<TypeAnnotation> parse(Token& token);

	bool validate(SymbolTable& symbols);

	const auto& token() const { return _token; }
	const auto& type() const { return *_type; }
	// const auto& type() const { return _type; }
};

#endif
