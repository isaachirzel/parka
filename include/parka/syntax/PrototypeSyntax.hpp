#ifndef PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP

#include "parka/context/PrototypeContext.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

namespace parka
{
	class PrototypeSyntax
	{
		KeywordSyntax _keyword;
		Identifier _identifier;
		Array<ParameterSyntax*> _parameters;
		Optional<TypeAnnotationSyntax> _returnType;

	public:

		PrototypeSyntax(KeywordSyntax&& keyword, Identifier&& identifier, Array<ParameterSyntax*>&& parameters, Optional<TypeAnnotationSyntax>&& returnType);
		PrototypeSyntax(PrototypeSyntax&&) = default;
		PrototypeSyntax(const PrototypeSyntax&) = delete;

		static Optional<PrototypeSyntax> parse(Token& token);

		Optional<PrototypeContext> validate(SymbolTable& symbolTable);

		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
