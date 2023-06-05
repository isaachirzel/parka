#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	struct ExpressionSyntax;
	class AdditiveExpressionSyntax;
	class AssignmentExpressionSyntax;
	class BitwiseAndExpressionSyntax;
	class BitwiseOrExpressionSyntax;
	class BitwiseXorExpressionSyntax;
	class BlockSyntax;
	class BooleanAndExpressionSyntax;
	class BooleanOrExpressionSyntax;
	class CallExpressionSyntax;
	class ConditionalExpressionSyntax;
	class EqualityExpressionSyntax;
	class IdentifierExpressionSyntax;
	class IfExpressionSyntax;
	class SubscriptExpressionSyntax;
	class MemberAccessExpressionSyntax;
	class MultiplicativeExpressionSyntax;
	class PrefixExpressionSyntax;
	class RelationalExpressionSyntax;
	class ShiftExpressionSyntax;
	class BoolLiteralSyntax;
	class CharLiteralSyntax;
	class FloatLiteralSyntax;
	class IntegerLiteralSyntax;
	class StringLiteralSyntax;

	class ExpressionSyntaxId
	{
		usize _index;
		ExpressionType _type;

	private:

		ExpressionSyntaxId(ExpressionType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:
		
		ExpressionSyntaxId(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId(const ExpressionSyntaxId&) = default;

		static ExpressionSyntaxId create(AdditiveExpressionSyntax&&);
		static ExpressionSyntaxId create(AssignmentExpressionSyntax&&);
		static ExpressionSyntaxId create(BitwiseAndExpressionSyntax&&);
		static ExpressionSyntaxId create(BitwiseOrExpressionSyntax&&);
		static ExpressionSyntaxId create(BitwiseXorExpressionSyntax&&);
		static ExpressionSyntaxId create(BlockSyntax&&);
		static ExpressionSyntaxId create(BooleanAndExpressionSyntax&&);
		static ExpressionSyntaxId create(BooleanOrExpressionSyntax&&);
		static ExpressionSyntaxId create(CallExpressionSyntax&&);
		static ExpressionSyntaxId create(ConditionalExpressionSyntax&&);
		static ExpressionSyntaxId create(EqualityExpressionSyntax&&);
		static ExpressionSyntaxId create(IdentifierExpressionSyntax&&);
		static ExpressionSyntaxId create(IfExpressionSyntax&&);
		static ExpressionSyntaxId create(SubscriptExpressionSyntax&&);
		static ExpressionSyntaxId create(MemberAccessExpressionSyntax&&);
		static ExpressionSyntaxId create(MultiplicativeExpressionSyntax&&);
		static ExpressionSyntaxId create(PrefixExpressionSyntax&&);
		static ExpressionSyntaxId create(RelationalExpressionSyntax&&);
		static ExpressionSyntaxId create(ShiftExpressionSyntax&&);
		static ExpressionSyntaxId create(BoolLiteralSyntax&&);
		static ExpressionSyntaxId create(CharLiteralSyntax&&);
		static ExpressionSyntaxId create(FloatLiteralSyntax&&);
		static ExpressionSyntaxId create(IntegerLiteralSyntax&&);
		static ExpressionSyntaxId create(StringLiteralSyntax&&);

		const BlockSyntax& getBlock() const;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		ExpressionSyntaxId& operator=(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId& operator=(const ExpressionSyntaxId&) = default;
		friend std::ostream& operator<<(std::ostream& out, const ExpressionSyntaxId& id);
		bool operator==(const ExpressionSyntaxId& other) const;
		const ExpressionSyntax& operator*() const;
		const ExpressionSyntax *operator->() const;
	};
}

#endif
