#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrimitiveSyntax.hpp"
#include "parka/repository/Storage.hpp"
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
			auto id = Storage::add(std::move(expression));

			lhs = std::move(id);
			type = getAdditiveType(token);
		}

		return lhs;
	}

	// bool AdditiveExpressionSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto success = true;

	// 	if (!Storage::get(_lhs).validate(functionId))
	// 		success = false;

	// 	if (!Storage::get(_rhs).validate(functionId))
	// 		success = false;

	// 	// TODO: Test type compatibility

	// 	return success;
	// }

	// Optional<Type> AdditiveExpressionSyntax::getType() const
	// {
	// 	auto& lhs = Storage::get(_lhs);
	// 	auto& rhs = Storage::get(_rhs);
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
