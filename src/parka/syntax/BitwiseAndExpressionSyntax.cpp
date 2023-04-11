#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> BitwiseAndExpressionSyntax::parse(Token& token)
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
			auto id = Storage::add(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
