#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<MultiplicativeType> getMultiplicativeType(Token& token)
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

	const ExpressionSyntax *MultiplicativeExpressionSyntax::parse(Token& token)
	{
		auto lhs = PrefixExpressionSyntax::parse(token);

		if (!lhs)
			return {};
		
		auto type = getMultiplicativeType(token);

		while (type)
		{
			token.increment();
			
			auto rhs = PrefixExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = MultiplicativeExpressionSyntax(*lhs, *rhs, *type);
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
			type = getMultiplicativeType(token);
		}

		return lhs;
	}

	// bool MultiplicativeExpressionSyntax::validate(const EntitySyntax& function)
	// {
	// 	auto success = true;

	// 	if (!SyntaxRepository::get(_lhs).validate(function))
	// 		success = false;

	// 	if (!SyntaxRepository::get(_rhs).validate(function))
	// 		success = false;

	// 	return success;
	// }
}
