#include "parka/ast/BitwiseXorExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BitwiseAndExpression.hpp"

namespace parka
{
	BitwiseXorExpressionSyntax::BitwiseXorExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	ExpressionSyntax *BitwiseXorExpressionSyntax::parse(Token& token)
	{
		auto *lhs = BitwiseAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseXorExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionContext *BitwiseXorExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
