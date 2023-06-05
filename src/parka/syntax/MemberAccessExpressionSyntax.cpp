#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> MemberAccessExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
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
		auto id = ExpressionSyntaxId::create(std::move(expression));

		token.increment();

		return id;
	}
}
