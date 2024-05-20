#ifndef PARKA_AST_FUNCTION_AST_HPP
#define PARKA_AST_FUNCTION_AST_HPP

#include "parka/ast/FunctionBodyAst.hpp"
#include "parka/ast/PrototypeAst.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class FunctionAst
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		Optional<FunctionBodyAst> _body;

	public:
	
		FunctionAst(const Snippet& snippet, PrototypeAst&& prototype, Optional<FunctionBodyAst>&& body):
			_snippet(snippet),
			_prototype(std::move(prototype)),
			_body(std::move(body))
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
