#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/Parameter.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::ast
{
	class ParameterAst : public Declarable, public Resolvable
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationAst _annotation;
		SymbolTable *_parent;
		ir::ParameterIr *_context;
		bool _isMutable;

	public:

		ParameterAst(const Snippet& snippet, Identifier&& identifier, TypeAnnotationAst&& annotation, bool isMutable):
		Declarable(DeclarableType::Parameter),
		Resolvable(ResolvableType::Parameter),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_parent(nullptr),
		_isMutable(isMutable)
		{}
		ParameterAst(ParameterAst&&) = default;
		ParameterAst(const ParameterAst&) = delete;

		String getSymbol() const;

		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }		
		const Snippet& snippet() const { return _snippet; }

		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }

		friend std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax);
	};
}

#endif
