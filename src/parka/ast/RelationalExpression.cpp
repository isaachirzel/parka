#include "parka/ast/RelationalExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/ShiftExpression.hpp"

namespace parka::ast
{
	static Optional<RelationalType> parseRelationalType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return RelationalType::GreaterThan;

			case TokenType::LessThan:
				return RelationalType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return RelationalType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return RelationalType::LessThanOrEqualTo;

			default:
				return {};
		}
	}
	
	ExpressionAst *RelationalExpressionAst::parse(Token& token)
	{
		auto *lhs = ShiftExpressionAst::parse(token);

		if (!lhs)
			return {};

		auto type = parseRelationalType(token);

		while (type)
		{
			token.increment();

			auto rhs = ShiftExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new RelationalExpressionAst(*lhs, *rhs, *type);
			type = parseRelationalType(token);
		}

		return lhs;
	}

	ir::ExpressionIr *RelationalExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}