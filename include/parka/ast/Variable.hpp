#ifndef PARKA_AST_VARIABLE_HPP
#define PARKA_AST_VARIABLE_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Variable.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/TypeAnnotation.hpp"

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
