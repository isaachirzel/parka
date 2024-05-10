#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/PrototypeAst.hpp"

namespace parka::ast
{
	class FunctionAst
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		BlockStatementAst& _body;

	public:

		FunctionAst(PrototypeAst&& prototype, BlockStatementAst& body):
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
