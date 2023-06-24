#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/SymbolTable.hpp"

namespace parka::ast
{
	class FunctionAst : public Declarable
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		ExpressionAst& _body;

	public:

		FunctionAst(PrototypeAst&& prototype, ExpressionAst& body):
		Declarable(DeclarableType::Function),
		_snippet(prototype.snippet() + body.snippet()),
		_prototype(std::move(prototype)),
		_body(body)
		{}
		FunctionAst(FunctionAst&&) = default;
		FunctionAst(const FunctionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const String& name() const { return _prototype.identifier().text(); }
		const Identifier& identifier() const { return _prototype.identifier(); }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
