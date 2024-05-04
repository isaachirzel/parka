#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"

namespace parka::ast
{
	class FunctionAst
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		ExpressionAst& _body;

	public:

		FunctionAst(PrototypeAst&& prototype, ExpressionAst& body):
			_snippet(prototype.snippet() + body.snippet()),
			_prototype(std::move(prototype)),
			_body(body)
		{}
		FunctionAst(FunctionAst&&) = default;
		FunctionAst(const FunctionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
