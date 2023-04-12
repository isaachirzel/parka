#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	Optional<AdditiveType> getAdditiveType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return AdditiveType::Add;

			case TokenType::Minus:
				return AdditiveType::Subtract;

			default:
				break;
		}

		return {};
	}

	Optional<ExpressionSyntaxId> AdditiveExpressionSyntax::parse(Token& token)
	{
		auto lhs = MultiplicativeExpressionSyntax::parse(token);

		if (!lhs)
			return {};
		
		auto type = getAdditiveType(token);

		while (type)
		{
			token.increment();

			auto rhs = MultiplicativeExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = AdditiveExpressionSyntax(*lhs, *rhs, *type);
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
			type = getAdditiveType(token);
		}

		return lhs;
	}

	// bool AdditiveExpressionSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto success = true;

	// 	if (!SyntaxRepository::get(_lhs).validate(functionId))
	// 		success = false;

	// 	if (!SyntaxRepository::get(_rhs).validate(functionId))
	// 		success = false;

	// 	// TODO: Test type compatibility

	// 	return success;
	// }

	// Optional<Type> AdditiveExpressionSyntax::getType() const
	// {
	// 	auto& lhs = SyntaxRepository::get(_lhs);
	// 	auto& rhs = SyntaxRepository::get(_rhs);
	// 	auto leftType = lhs.getType();
	// 	auto rightType = rhs.getType();

	// 	if (!leftType || !rightType)
	// 		return {};

	// 	print("Left type: $", *leftType);
	// 	print("Right type: $", *rightType);

	// 	// TODO: Operators

	// 	if (!rightType->canConvertTo(*leftType))
	// 	{
	// 		printError("A value of type $ cannot be added to $", *rightType, *leftType);
	// 		return {};
	// 	}
		
	// 	return *leftType;
	// }
}
