#include "parka/ast/MultiplicativeExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/PrefixExpression.hpp"

namespace parka::ast
{
	static Optional<MultiplicativeType> getMultiplicativeType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Modulus:
				return MultiplicativeType::Modulus;

			case TokenType::Asterisk:
				return MultiplicativeType::Multiply;

			case TokenType::Slash:
				return MultiplicativeType::Divide;

			default:
				return {};
		}
	}

	ExpressionAst *MultiplicativeExpressionAst::parse(Token& token)
	{
		auto *lhs = PrefixExpressionAst::parse(token);

		if (!lhs)
			return {};
		
		auto type = getMultiplicativeType(token);

		while (type)
		{
			token.increment();
			
			auto rhs = PrefixExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new MultiplicativeExpressionAst(*lhs, *rhs, *type);
			type = getMultiplicativeType(token);
		}

		return lhs;
	}

	ir::ExpressionIr *MultiplicativeExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}