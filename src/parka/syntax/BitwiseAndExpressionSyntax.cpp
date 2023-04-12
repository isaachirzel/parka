#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BitwiseAndExpressionSyntax::parse(Token& token)
	{
		auto lhs = EqualityExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = EqualityExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BitwiseAndExpressionSyntax(*lhs, *rhs);
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
