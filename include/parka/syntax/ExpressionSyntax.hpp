#ifndef PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/context/ExpressionContext.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct ExpressionSyntax
	{
		virtual ~ExpressionSyntax() {}
		virtual ExpressionType expressionType() const = 0;

		static ExpressionSyntax *parse(Token& token);
		virtual ExpressionContext *validate(SymbolTable& symbolTable) = 0;
	};
}

#endif
