#ifndef PARKA_CONTEXT_HPP
#define PARKA_CONTEXT_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/data/EntitySyntax.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/data/ExpressionId.hpp"
#include "parka/data/StatementId.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSyntax;
	class PrimitiveSyntax;
	class StructSyntax;
	class FunctionSyntax;
	class VariableSyntax;
	class ParameterSyntax;
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
	class DeclarationStatementSyntax;
	class ExpressionStatementSyntax;
	class JumpStatementSyntax;

	struct Storage
	{
		static const EntityId voidId;
		static const EntityId u8Id;
		static const EntityId u16Id;
		static const EntityId u32Id;
		static const EntityId u64Id;
		static const EntityId i8Id;
		static const EntityId i16Id;
		static const EntityId i32Id;
		static const EntityId i64Id;
		static const EntityId f32Id;
		static const EntityId f64Id;
		static const EntityId boolId;
		static const EntityId charId;
		static const EntityId stringId;

		static void initialize();

		static EntityId add(PackageSyntax&& value);
		static EntityId add(StructSyntax&& value);
		static EntityId add(FunctionSyntax&& value);
		static EntityId add(VariableSyntax&& value);
		static EntityId add(ParameterSyntax&& value);

		static ExpressionId add(AdditiveExpressionSyntax&& value);
		static ExpressionId add(AssignmentExpressionSyntax&& value);
		static ExpressionId add(BitwiseAndExpressionSyntax&& value);
		static ExpressionId add(BitwiseOrExpressionSyntax&& value);
		static ExpressionId add(BitwiseXorExpressionSyntax&& value);
		static ExpressionId add(BlockSyntax&& value);
		static ExpressionId add(BooleanAndExpressionSyntax&& value);
		static ExpressionId add(BooleanOrExpressionSyntax&& value);
		static ExpressionId add(CallExpressionSyntax&& value);
		static ExpressionId add(ConditionalExpressionSyntax&& value);
		static ExpressionId add(EqualityExpressionSyntax&& value);
		static ExpressionId add(IdentifierExpressionSyntax&& value);
		static ExpressionId add(IfExpressionSyntax&& value);
		static ExpressionId add(SubscriptExpressionSyntax&& value);
		static ExpressionId add(MemberAccessExpressionSyntax&& value);
		static ExpressionId add(MultiplicativeExpressionSyntax&& value);
		static ExpressionId add(PrefixExpressionSyntax&& value);
		static ExpressionId add(RelationalExpressionSyntax&& value);
		static ExpressionId add(ShiftExpressionSyntax&& value);

		// Literals
		static ExpressionId add(BoolLiteralSyntax&& value);
		static ExpressionId add(CharLiteralSyntax&& value);
		static ExpressionId add(FloatLiteralSyntax&& value);
		static ExpressionId add(IntegerLiteralSyntax&& value);
		static ExpressionId add(StringLiteralSyntax&& value);

		// Statements
		static StatementId add(DeclarationStatementSyntax&& value);
		static StatementId add(ExpressionStatementSyntax&& value);
		static StatementId add(JumpStatementSyntax&& value);

		static EntitySyntax& get(const EntityId& id);
		static ExpressionSyntax& get(const ExpressionId& id);
		static StatementSyntax& get(const StatementId& id);

		static PackageSyntax& getPackage(const EntityId& id);
		static StructSyntax& getStruct(const EntityId& id);
		static FunctionSyntax& getFunction(const EntityId& id);
		static VariableSyntax& getVariable(const EntityId& id);
		static ParameterSyntax& getParameter(const EntityId& id);

		static EntityId getId(FunctionSyntax& value);
		static EntityId getId(PackageSyntax& value);
		
		static void declarePrimitives(Table<String, EntityId>& globalSymbols);
		static usize getGlobalCount();
		static usize getPackageCount();
	};
}

#endif
