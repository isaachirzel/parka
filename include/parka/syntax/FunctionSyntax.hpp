#ifndef PARKA_SYNTAX_FUNCTION_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_SYNTAX_HPP

#include "parka/syntax/PrototypeSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/type/Type.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class FunctionSyntax : public EntitySyntax
	{
		PrototypeSyntax _prototype;
		ExpressionSyntaxId _body;

		FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntaxId&& body) :
		_prototype(std::move(prototype)),
		_body(std::move(body))
		{}

	public:

		FunctionSyntax(FunctionSyntax&&) = default;
		FunctionSyntax(const FunctionSyntax&) = delete;

		static Optional<EntitySyntaxId> parse(Token& token);
		
		const String& identifier() const { return _prototype.identifier().text(); }
		EntityType type() const { return EntityType::Function; }
		const auto& body() const { return _body; }
	};
}

#endif
