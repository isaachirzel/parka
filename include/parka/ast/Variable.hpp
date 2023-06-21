#ifndef PARKA_AST_VARIABLE_HPP
#define PARKA_AST_VARIABLE_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/enum/DeclarableType.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Variable.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/TypeAnnotation.hpp"

namespace parka::ast
{
	class VariableAst : public Declarable
	{
		Snippet _snippet;
		Identifier _identifier;
		Optional<TypeAnnotationAst> _annotation;
		ir::VariableIr *_context;
		bool _isMutable;

	public:

		VariableAst(const Snippet& snippet, Identifier&& identifier, bool isMutable, Optional<TypeAnnotationAst> annotation) :
		Declarable(DeclarableType::Variable, ResolvableType::Variable),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isMutable(isMutable)
		{}
		VariableAst(VariableAst&&) = default;
		VariableAst(const VariableAst&) = delete;

		static VariableAst *parse(Token& token);
		String getSymbol() const { return _identifier.text(); }

		const Snippet& snippet() const { return _snippet; }
		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }
		const auto& isExplicitlyTyped() const { return _annotation.hasValue(); }
		const auto& annotation() const { return *_annotation; }
		const auto& isMutable() const { return _isMutable; }
	};

	
}

#endif
