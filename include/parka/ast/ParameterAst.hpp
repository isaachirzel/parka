#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ir/ParameterIr.hpp"

namespace parka::ast
{
	class ParameterAst
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationAst _annotation;
		SymbolTable *_parent;
		ir::ParameterIr *_context;
		bool _isMutable;

	public:

		ParameterAst(const Snippet& snippet, Identifier&& identifier, TypeAnnotationAst&& annotation, bool isMutable):
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_parent(nullptr),
		_isMutable(isMutable)
		{}
		ParameterAst(ParameterAst&&) = default;
		ParameterAst(const ParameterAst&) = delete;

		String getSymbol() const;

		const auto& identifier() const { return _identifier; }		
		const auto& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }

		friend std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax);
	};
}

#endif
