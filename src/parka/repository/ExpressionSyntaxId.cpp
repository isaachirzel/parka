#include "parka/log/Log.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/syntax/CharLiteralSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/FloatLiteralSyntax.hpp"
#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/syntax/StringLiteralSyntax.hpp"
#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	static Pool<AdditiveExpressionSyntax> additiveExpressions(100'000'000);
	static Pool<AssignmentExpressionSyntax> assignmentExpressions(100'000'000);
	static Pool<BitwiseAndExpressionSyntax> bitwiseAndExpressions(100'000'000);
	static Pool<BitwiseOrExpressionSyntax> bitwiseOrExpressions(100'000'000);
	static Pool<BitwiseXorExpressionSyntax> bitwiseXorExpressions(100'000'000);
	static Pool<BlockSyntax> blockExpressions(100'000'000);
	static Pool<BooleanAndExpressionSyntax> booleanAndExpressions(100'000'000);
	static Pool<BooleanOrExpressionSyntax> booleanOrExpressions(100'000'000);
	static Pool<CallExpressionSyntax> callExpressions(100'000'000);
	static Pool<ConditionalExpressionSyntax> conditionalExpressions(100'000'000);
	static Pool<EqualityExpressionSyntax> equalityExpressions(100'000'000);
	static Pool<IdentifierExpressionSyntax> identifierExpressions(100'000'000);
	static Pool<SubscriptExpressionSyntax> subscriptExpressions(100'000'000);
	static Pool<MemberAccessExpressionSyntax> memberAccessExpressions(100'000'000);
	static Pool<MultiplicativeExpressionSyntax> multiplicativeExpressions(100'000'000);
	static Pool<PrefixExpressionSyntax> prefixExpressions(100'000'000);
	static Pool<RelationalExpressionSyntax> relationalExpressions(100'000'000);
	static Pool<ShiftExpressionSyntax> shiftExpressions(100'000'000);
	static Pool<BoolLiteralSyntax> boolLiterals(1'000'000);
	static Pool<CharLiteralSyntax> charLiterals(1'000'000);
	static Pool<FloatLiteralSyntax> floatLiterals(1'000'000);
	static Pool<IntegerLiteralSyntax> integerLiterals(1'000'000);
	static Pool<StringLiteralSyntax> stringLiterals(1'000'000);

	ExpressionSyntaxId ExpressionSyntaxId::create(AdditiveExpressionSyntax&& value)
	{
		auto index = additiveExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Additive, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(AssignmentExpressionSyntax&& value)
	{
		auto index = assignmentExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Assignment, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BitwiseAndExpressionSyntax&& value)
	{
		auto index = bitwiseAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseAnd, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BitwiseOrExpressionSyntax&& value)
	{
		auto index = bitwiseOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseOr, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BitwiseXorExpressionSyntax&& value)
	{
		auto index = bitwiseXorExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseXor, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BlockSyntax&& value)
	{
		auto index = blockExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Block, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BooleanAndExpressionSyntax&& value)
	{
		auto index = booleanAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanAnd, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BooleanOrExpressionSyntax&& value)
	{
		auto index = booleanOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanOr, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(CallExpressionSyntax&& value)
	{
		auto index = callExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Call, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(ConditionalExpressionSyntax&& value)
	{
		auto index = conditionalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Conditional, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(EqualityExpressionSyntax&& value)
	{
		auto index = equalityExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Equality, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(IdentifierExpressionSyntax&& value)
	{
		auto index = identifierExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IdentifierExpression, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(SubscriptExpressionSyntax&& value)
	{
		auto index = subscriptExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Subscript, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(MemberAccessExpressionSyntax&& value)
	{
		auto index = memberAccessExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::MemberAccessExpression, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(MultiplicativeExpressionSyntax&& value)
	{
		auto index = multiplicativeExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Multiplicative, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(PrefixExpressionSyntax&& value)
	{
		auto index = prefixExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::PrefixExpression, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(RelationalExpressionSyntax&& value)
	{
		auto index = relationalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Relational, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(ShiftExpressionSyntax&& value)
	{
		auto index = shiftExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Shift, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(BoolLiteralSyntax&& value)
	{
		auto index = boolLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BoolLiteral, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(CharLiteralSyntax&& value)
	{
		auto index = charLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::CharLiteral, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(FloatLiteralSyntax&& value)
	{
		auto index = floatLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::FloatLiteral, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(IntegerLiteralSyntax&& value)
	{
		auto index = integerLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IntegerLiteral, index);
	}

	ExpressionSyntaxId ExpressionSyntaxId::create(StringLiteralSyntax&& value)
	{
		auto index = stringLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::StringLiteral, index);
	}

	const ExpressionSyntax& ExpressionSyntaxId::operator*() const
	{
		switch (_type)
		{
			case ExpressionType::Additive:
				return additiveExpressions[_index];

			case ExpressionType::Assignment:
				return assignmentExpressions[_index];

			case ExpressionType::BitwiseAnd:
				return bitwiseAndExpressions[_index];

			case ExpressionType::BitwiseOr:
				return bitwiseOrExpressions[_index];

			case ExpressionType::BitwiseXor:
				return bitwiseXorExpressions[_index];

			case ExpressionType::Block:
				return blockExpressions[_index];

			case ExpressionType::BooleanAnd:
				return booleanAndExpressions[_index];

			case ExpressionType::BooleanOr:
				return booleanOrExpressions[_index];

			case ExpressionType::Call:
				return callExpressions[_index];

			case ExpressionType::Conditional:
				return conditionalExpressions[_index];

			case ExpressionType::Equality:
				return equalityExpressions[_index];

			case ExpressionType::IdentifierExpression:
				return identifierExpressions[_index];

			case ExpressionType::If:
				// TODO: Implemente get for If
				break;
				// return ifExpressions[_index];

			case ExpressionType::Subscript:
				return subscriptExpressions[_index];

			case ExpressionType::MemberAccessExpression:
				return memberAccessExpressions[_index];

			case ExpressionType::Multiplicative:
				return multiplicativeExpressions[_index];

			case ExpressionType::PrefixExpression:
				return prefixExpressions[_index];

			case ExpressionType::Relational:
				return relationalExpressions[_index];

			case ExpressionType::Shift:
				return shiftExpressions[_index];

			case ExpressionType::BoolLiteral:
				return boolLiterals[_index];
				
			case ExpressionType::CharLiteral:
				return charLiterals[_index];
				
			case ExpressionType::FloatLiteral:
				return floatLiterals[_index];
				
			case ExpressionType::IntegerLiteral:
				return integerLiterals[_index];
				
			case ExpressionType::StringLiteral:
				return stringLiterals[_index];
				
			default:
				break;
		}

		Log::fatal("Unable to get ExpressionSyntax of type: $", (int)_type);
	}
}
