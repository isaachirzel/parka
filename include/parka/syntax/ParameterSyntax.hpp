#ifndef PARKA_SYNTAX_PARAMETER_SYNTAX_HPP
#define PARKA_SYNTAX_PARAMETER_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/syntax/EntitySyntax.hpp"

namespace parka
{
	class ParameterSyntax : public EntitySyntax
	{
		Identifier _identifier;
		TypeAnnotationSyntax _annotation;
		bool _isMutable;

		ParameterSyntax(Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isMutable) :
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isMutable(isMutable)
		{}

	public:

		ParameterSyntax(ParameterSyntax&&) = default;
		ParameterSyntax(const ParameterSyntax&) = delete;

		static Optional<EntitySyntaxId> parse(Token& token);

		const String& identifier() const { return _identifier.text(); }
		EntityType type() const { return EntityType::Parameter; }

		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }
	};
}

#endif
