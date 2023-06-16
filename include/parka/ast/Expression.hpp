#ifndef PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}
		virtual const ValueType& valueType() const = 0;
		virtual ExpressionType expressionType() const = 0;
	};

	struct ExpressionSyntax
	{
		// TODO: Add snippets to expression
		virtual ~ExpressionSyntax() {}
		virtual ExpressionType expressionType() const = 0;
		virtual const Snippet& snippet() const = 0;
		virtual ExpressionContext *validate(SymbolTable& symbolTable) = 0;
		
		static ExpressionSyntax *parse(Token& token);
	};
}

#endif
