#ifndef PARKA_SYNTAX_VARIABLE_SYNTAX_HPP
#define PARKA_SYNTAX_VARIABLE_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Entity.hpp"

namespace parka
{
	class VariableContext: public EntityContext
	{
		String _symbol;
		ValueType _type;
	
	public:

		VariableContext(String&& symbol, ValueType&& type);
		VariableContext(VariableContext&&) = default;
		VariableContext(const VariableContext&) = delete;

		const String& symbol() const { return _symbol; }
		EntityType entityType() const { return EntityType::Variable; }
		const auto& valueType() const { return _type; }
	};

	class VariableSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Optional<TypeAnnotationSyntax> _annotation;
		VariableContext *_context;
		bool _isMutable;

	public:

		VariableSyntax(Identifier&& identifier, bool isMutable, Optional<TypeAnnotationSyntax> annotation);
		VariableSyntax(VariableSyntax&&) = default;
		VariableSyntax(const VariableSyntax&) = delete;

		static VariableSyntax *parse(Token& token);
		VariableContext *validate(SymbolTable& symbolTable, ExpressionContext *value);
		EntityContext *context() { assert(_context != nullptr); return _context; }
		String getSymbol() const { return _identifier.text(); }

		EntityType entityType() const { return EntityType::Variable; }
		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }
		const auto& isExplicitlyTyped() const { return _annotation.hasValue(); }
		const auto& annotation() const { return *_annotation; }
		const auto& isMutable() const { return _isMutable; }
	};

	
}

#endif