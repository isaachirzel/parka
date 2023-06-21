#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/Parameter.hpp"
#include "parka/symbol/Declarable.hpp"

namespace parka::ast
{
	class ParameterAst : public Declarable
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationAst _annotation;
		SymbolTable *_parent;
		ir::ParameterIr *_context;
		bool _isMutable;

	public:

		ParameterAst(const Snippet& snippet, Identifier&& identifier, TypeAnnotationAst&& annotation, bool isMutable) :
		Declarable(DeclarableType::Parameter, ResolvableType::Parameter),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_parent(nullptr),
		_isMutable(isMutable)
		{}
		ParameterAst(ParameterAst&&) = default;
		ParameterAst(const ParameterAst&) = delete;

		static ParameterAst *parse(Token& token);

		ir::ParameterIr *validate(SymbolTable& symbolTable);
		ir::EntityIr *context() { assert(_context != nullptr); return _context; }
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
