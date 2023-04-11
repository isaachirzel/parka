#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> BitwiseXorExpressionSyntax::parse(Token& token)
	{
		auto lhs = BitwiseAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BitwiseXorExpressionSyntax(*lhs, *rhs);
			auto id = Storage::add(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
