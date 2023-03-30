#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/symbol/symbol_table.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/util/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class TypeAnnotation
{
	Token _token;
	// // TODO: Add type after validation
	Optional<Type> _type; // Having an optional type is causing this a free warning to come up

	TypeAnnotation(const Token& token) :
	_token(token),
	_type()
	{}

public:

	TypeAnnotation(TypeAnnotation&&) = default;
	TypeAnnotation(const TypeAnnotation&) = delete;
	~TypeAnnotation() = default;

	static Optional<TypeAnnotation> parse(Token& token);

	bool validate(SymbolTable& symbols);

	const Token& token() const { return _token; }
	const Type& type() const { throw std::exception(); }//return *_type; }
	// const auto& type() const { return _type; }
};

#endif
