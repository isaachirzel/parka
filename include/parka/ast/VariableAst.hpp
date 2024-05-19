#ifndef PARKA_AST_VARIABLE_AST_HPP
#define PARKA_AST_VARIABLE_AST_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class VariableAst
	{
		Snippet _snippet;
		Identifier _identifier;
		Optional<TypeAnnotationAst> _annotation;
		bool _isMutable;

	public:

		VariableAst(const Snippet& snippet, Identifier&& identifier, bool isMutable, Optional<TypeAnnotationAst> annotation):
			_snippet(snippet),
			_identifier(std::move(identifier)),
			_annotation(std::move(annotation)),
			_isMutable(isMutable)
		{}
		VariableAst(VariableAst&&) = default;
		VariableAst(const VariableAst&) = delete;

		String getSymbol() const { return _identifier.text(); }

		const auto& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }
	};

	
}

#endif
