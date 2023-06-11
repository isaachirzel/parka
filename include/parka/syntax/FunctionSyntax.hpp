#ifndef PARKA_SYNTAX_FUNCTION_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_SYNTAX_HPP

#include "parka/syntax/PrototypeSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/type/ValueType.hpp"
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
		ExpressionSyntax& _body;

	public:

		FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body);
		FunctionSyntax(FunctionSyntax&&) = default;
		FunctionSyntax(const FunctionSyntax&) = delete;

		static FunctionSyntax *parse(Token& token);
		
		

		EntityType entityType() const { return EntityType::Function; }
		const String& identifier() const { return _prototype.identifier().text(); }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
