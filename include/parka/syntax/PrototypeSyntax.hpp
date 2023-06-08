#ifndef PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

namespace parka
{
	class PrototypeSyntax
	{
		KeywordSyntax _keyword;
		Identifier _identifier;
		Array<const ParameterSyntax*> _parameters;
		Optional<TypeAnnotationSyntax> _returnType;

		PrototypeSyntax(KeywordSyntax&& keyword, Identifier&& identifier, Array<const ParameterSyntax*>&& parameters, Optional<TypeAnnotationSyntax>&& returnType) :
		_keyword(std::move(keyword)),
		_identifier(std::move(identifier)),
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}

	public:

		PrototypeSyntax(PrototypeSyntax&&) = default;
		PrototypeSyntax(const PrototypeSyntax&) = delete;

		static Optional<PrototypeSyntax> parse(Token& token);

		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
