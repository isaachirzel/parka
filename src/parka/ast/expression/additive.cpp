#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/multiplicative.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

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

Optional<ExpressionId> AdditiveExpression::parse(Token& token)
{
	auto lhs = MultiplicativeExpression::parse(token);

	if (!lhs)
		return {};
	
	auto type = getAdditiveType(token);

	while (type)
	{
		token.increment();

		auto rhs = MultiplicativeExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = AdditiveExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = getAdditiveType(token);
	}

	return lhs;
}

bool AdditiveExpression::validate(const EntityId& functionId)
{
	auto success = true;

	if (!NodeBank::get(_lhs).validate(functionId))
		success = false;

	if (!NodeBank::get(_rhs).validate(functionId))
		success = false;

	// TODO: Test type compatibility

	return success;
}

Optional<Type> AdditiveExpression::getType() const
{
	auto& lhs = NodeBank::get(_lhs);
	auto& rhs = NodeBank::get(_rhs);
	auto leftType = lhs.getType();
	auto rightType = rhs.getType();

	if (!leftType || !rightType)
		return {};

	print("Left type: `$`", *leftType);
	print("Right type: `$`", *rightType);

	// TODO: Operators

	if (!rightType->canConvertTo(*leftType))
	{
		printError("A value of type $ cannot be added to $", *rightType, *leftType);
		return {};
	}
	
	return *leftType;
}
