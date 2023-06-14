#ifndef PARKA_SYNTAX_VARIABLE_SYNTAX_HPP
#define PARKA_SYNTAX_VARIABLE_SYNTAX_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/context/VariableContext.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/syntax/EntitySyntax.hpp"

namespace parka
{
	class VariableSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Optional<TypeAnnotationSyntax> _annotation;
		bool _isMutable;

	public:

		VariableSyntax(Identifier&& identifier, bool isMutable, Optional<TypeAnnotationSyntax> annotation);
		VariableSyntax(VariableSyntax&&) = default;
		VariableSyntax(const VariableSyntax&) = delete;

		static VariableSyntax *parse(Token& token);
		VariableContext *validate(SymbolTable& symbolTable, ExpressionContext *value);

		const String& identifier() const { return _identifier.text(); }
		EntityType entityType() const { return EntityType::Variable; }
		const auto& isExplicitlyTyped() const { return _annotation.hasValue(); }
		const auto& annotation() const { return *_annotation; }
		const auto& isMutable() const { return _isMutable; }
	};
}

#endif
