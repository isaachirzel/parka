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

Optional<Type> getSignedIntegerType(const Primitive&, const Primitive& right, Ref<Type>)
{
	switch (right.primitiveType())
	{
		case PRIMITIVE_SIGNED_INTEGER:
			// TODO: Actually check the bytes
			return Type(NodeBank::i32Id);

		default:
			break;
	}
	
	return {};
}

Optional<Type> getPrimitiveType(const Primitive&, const Primitive&, Ref<Type>)
{
	exitNotImplemented(here());
	// switch (left.type())
	// {
	// 	case PRIMITIVE_SIGNED_INTEGER:
	// 		return getSignedIntegerType(left, right, expected);

	// 	default:
	// 		break;
	// }

	return {};
}

Optional<Type> AdditiveExpression::getType(Ref<Type>) const
{

	exitNotImplemented(here());

	// auto leftType = _lhs->getType(symbols, expected);

	// if (!leftType)
	// 	return {};

	// auto rightType = _rhs->getType(symbols, expected);

	// if (!rightType)
	// 	return {};

	// auto leftId = leftType->entityId();

	// if (leftId.type() == EntityType::Primitive)
	// {
	// 	const auto& leftPrimitive = symbols.getEntity(leftId);
	// 	// const Primitive *leftPrimitive = symbolTableGetPrimitive(leftType->index());
		
	// 	auto rightId = rightType->entityId();

	// 	if (rightId.type() == EntityType::Primitive)
	// 	{
	// 		const Primitive *rightPrimitive = symbolTableGetPrimitive(rightType->index());

	// 		auto primitiveType = getPrimitiveType(leftPrimitive, rightPrimitive, expected);

	// 		if (primitiveType)
	// 			return primitiveType;
	// 	}
	// 	else
	// 	{
	// 		exitWithError("Primitive + Complex is not implemented yet.");
	// 	}
	// }
	// else
	// {
	// 	exitWithError("Addition for complex types is not implemented yet.");
	// }
	
	// printError("`$` cannot be added to `$`.", rightType.name() typeGetName(&rightType), typeGetName(&leftType));

	return {};
}
