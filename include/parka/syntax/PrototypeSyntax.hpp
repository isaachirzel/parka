#ifndef PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

namespace parka
{
	class PrototypeSyntax
	{
		KeywordSyntax _keyword;
		Identifier _identifier;
		Array<EntitySyntaxId> _parameterIds;
		Optional<TypeAnnotationSyntax> _returnType;

		PrototypeSyntax(KeywordSyntax&& keyword, Identifier&& identifier, Array<EntitySyntaxId>&& parameterIds, Optional<TypeAnnotationSyntax>&& returnType) :
		_keyword(std::move(keyword)),
		_identifier(std::move(identifier)),
		_parameterIds(std::move(parameterIds)),
		_returnType(std::move(returnType))
		{}

	public:

		PrototypeSyntax(PrototypeSyntax&&) = default;
		PrototypeSyntax(const PrototypeSyntax&) = delete;

		static Optional<PrototypeSyntax> parse(Token& token);

		bool validate(const EntitySyntaxId& functionId);

		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameterIds; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
