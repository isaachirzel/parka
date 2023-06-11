#ifndef PARKA_SYNTAX_FUNCTION_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_SYNTAX_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/PrototypeSyntax.hpp"

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
