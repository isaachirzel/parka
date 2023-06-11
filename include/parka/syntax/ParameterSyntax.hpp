#ifndef PARKA_SYNTAX_PARAMETER_SYNTAX_HPP
#define PARKA_SYNTAX_PARAMETER_SYNTAX_HPP

#include "parka/context/ParameterContext.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
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

	public:

		ParameterSyntax(Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isMutable);
		ParameterSyntax(ParameterSyntax&&) = default;
		ParameterSyntax(const ParameterSyntax&) = delete;

		static ParameterSyntax *parse(Token& token);

		ParameterContext *validate(FunctionSymbolTable& symbolTable);

		const String& identifier() const { return _identifier.text(); }
		const auto& token() const { return _identifier.token(); }
		EntityType entityType() const { return EntityType::Parameter; }
		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }
	};
}

#endif
