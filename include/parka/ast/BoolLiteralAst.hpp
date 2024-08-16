#ifndef PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP
#define PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ast
{
	class BoolLiteralAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;
		bool _value;

	public:

		BoolLiteralAst(const fs::FileSnippet& snippet, bool value):
		ExpressionAst(ExpressionType::BoolLiteral),
		_snippet(snippet),
		_value(value)
		{}
		BoolLiteralAst(BoolLiteralAst&&) = default;
		BoolLiteralAst(const BoolLiteralAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
