#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/PrototypeAst.hpp"

namespace parka::ast
{
	class FunctionAst
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		BlockStatementAst* _body;

	public:
	
		FunctionAst(const Snippet& snippet, PrototypeAst&& prototype):
			_snippet(snippet),
			_prototype(std::move(prototype)),
			_body(nullptr)
		{}
		FunctionAst(const Snippet& snippet, PrototypeAst&& prototype, BlockStatementAst& body):
			_snippet(snippet),
			_prototype(std::move(prototype)),
			_body(&body)
		{}
		FunctionAst(FunctionAst&&) = default;
		FunctionAst(const FunctionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return !!_body; }
		const auto& body() const { assert(_body); return *_body; }
	};
}

#endif
