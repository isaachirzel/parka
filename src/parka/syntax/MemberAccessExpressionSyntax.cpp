#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *MemberAccessExpressionSyntax::parse(Token& token, const ExpressionSyntax& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			log::parseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "member, method, or property name");
			return {};
		}

		auto expression = MemberAccessExpressionSyntax(std::move(primary), token);
		auto& syntax = ExpressionSyntax::create(std::move(expression));

		token.increment();

		return &syntax;
	}
}
