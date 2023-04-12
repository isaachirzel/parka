#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
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

	Optional<ExpressionSyntaxId> MultiplicativeExpressionSyntax::parse(Token& token)
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
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
			type = getMultiplicativeType(token);
		}

		return lhs;
	}

	// bool MultiplicativeExpressionSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto success = true;

	// 	if (!SyntaxRepository::get(_lhs).validate(functionId))
	// 		success = false;

	// 	if (!SyntaxRepository::get(_rhs).validate(functionId))
	// 		success = false;

	// 	return success;
	// }
}
