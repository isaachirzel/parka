#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/Storage.hpp"
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

	Optional<ExpressionId> MultiplicativeExpressionSyntax::parse(Token& token)
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
			auto id = Storage::add(std::move(expression));

			lhs = std::move(id);
			type = getMultiplicativeType(token);
		}

		return lhs;
	}

	// bool MultiplicativeExpressionSyntax::validate(const EntityId& functionId)
	// {
	// 	auto success = true;

	// 	if (!Storage::get(_lhs).validate(functionId))
	// 		success = false;

	// 	if (!Storage::get(_rhs).validate(functionId))
	// 		success = false;

	// 	return success;
	// }
}
