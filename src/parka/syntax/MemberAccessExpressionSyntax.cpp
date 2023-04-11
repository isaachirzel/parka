#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> MemberAccessExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
	{
		if (token.type() != TokenType::Dot)
		{
			printParseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			printParseError(token, "member, method, or property name");
			return {};
		}

		auto expression = MemberAccessExpressionSyntax(std::move(primary), token);
		auto id = Storage::add(std::move(expression));

		token.increment();

		return id;
	}
}
