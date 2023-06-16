#include "parka/ast/EqualityExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/RelationalExpression.hpp"

namespace parka::ast
{
	static Optional<EqualityType> getEqualityType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return EqualityType::Equals;

			case TokenType::NotEquals:
				return EqualityType::NotEquals;

			default:
				return {};
		}
	}

	ExpressionAst *EqualityExpressionAst::parse(Token& token)
	{
		auto *lhs = RelationalExpressionAst::parse(token);

		if (!lhs)
			return {};

		auto type = getEqualityType(token);

		while (type)
		{
			token.increment();

			auto rhs = RelationalExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new EqualityExpressionAst(*lhs, *rhs, *type);
			type = getEqualityType(token);
		}

		return lhs;
	}

	ir::ExpressionIr *EqualityExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}