#ifndef PARKA_SYNTAX_VARIABLE_SYNTAX_HPP
#define PARKA_SYNTAX_VARIABLE_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/data/EntitySyntax.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/data/ExpressionId.hpp"

namespace parka
{
	class VariableSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Optional<TypeAnnotationSyntax> _annotation;
		bool _isMutable;

		VariableSyntax(Identifier&& identifier, bool isMutable, Optional<TypeAnnotationSyntax> annotation) :
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isMutable(isMutable)
		{}

	public:

		VariableSyntax(VariableSyntax&&) = default;
		VariableSyntax(const VariableSyntax&) = delete;
		~VariableSyntax() = default;

		static Optional<EntityId> parse(Token& token);

		const String& identifier() const { return _identifier.text(); }
		EntityType type() const { return EntityType::Variable; }
		const auto& isExplicitlyTyped() const { return _annotation.hasValue(); }
		const auto& annotation() const { return *_annotation; }
		const auto& isMutable() const { return _isMutable; }
	};
}

#endif
