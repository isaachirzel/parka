#ifndef PARKA_SYNTAX_PARAMETER_SYNTAX_HPP
#define PARKA_SYNTAX_PARAMETER_SYNTAX_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/symbol/Identifier.hpp"

namespace parka
{
	class ParameterContext : public EntityContext
	{
		ValueType _type;

	public:

		ParameterContext(ValueType&& type);
		ParameterContext(ParameterContext&&) = default;
		ParameterContext(const ParameterContext&) = delete;

		EntityType entityType() const { return EntityType::Parameter; }
		const auto& valueType() const { return _type; }
	};

	class ParameterSyntax : public EntitySyntax
	{
		Identifier _identifier;
		TypeAnnotationSyntax _annotation;
		SymbolTable *_parent;
		ParameterContext *_context;
		bool _isMutable;

	public:

		ParameterSyntax(Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isMutable);
		ParameterSyntax(ParameterSyntax&&) = default;
		ParameterSyntax(const ParameterSyntax&) = delete;

		static ParameterSyntax *parse(Token& token);

		ParameterContext *validate(SymbolTable& symbolTable);
		EntityContext *context() { assert(_context != nullptr); return _context; }

		const String& name() const { return _identifier.text(); }
		const auto& token() const { return _identifier.token(); }
		const auto& identifier() const { return _identifier; }
		EntityType entityType() const { return EntityType::Parameter; }
		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }

		friend std::ostream& operator<<(std::ostream& out, const ParameterSyntax& syntax);
	};
}

#endif
