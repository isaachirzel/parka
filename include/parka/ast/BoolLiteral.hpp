#ifndef PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP
#define PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ir/Expression.hpp"

namespace parka::ast
{
	class BoolLiteralAst : public ExpressionAst
	{
		Snippet _snippet;
		bool _value;

	public:

		BoolLiteralAst(const Snippet& snippet, bool value) :
		_snippet(snippet),
		_value(value)
		{}
		BoolLiteralAst(BoolLiteralAst&&) = default;
		BoolLiteralAst(const BoolLiteralAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const Snippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
