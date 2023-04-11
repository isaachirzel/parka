#include "parka/repository/Storage.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/IfExpressionSyntax.hpp"
#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/syntax/CharLiteralSyntax.hpp"
#include "parka/syntax/FloatLiteralSyntax.hpp"
#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/syntax/StringLiteralSyntax.hpp"
#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/util/Array.hpp"
#include "parka/syntax/PrimitiveSyntax.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const EntitySyntaxId Storage::voidId(EntityType::Primitive, 0);
	const EntitySyntaxId Storage::u8Id(EntityType::Primitive, 1);
	const EntitySyntaxId Storage::u16Id(EntityType::Primitive, 2);
	const EntitySyntaxId Storage::u32Id(EntityType::Primitive, 3);
	const EntitySyntaxId Storage::u64Id(EntityType::Primitive, 4);
	const EntitySyntaxId Storage::i8Id(EntityType::Primitive, 5);
	const EntitySyntaxId Storage::i16Id(EntityType::Primitive, 6);
	const EntitySyntaxId Storage::i32Id(EntityType::Primitive, 7);
	const EntitySyntaxId Storage::i64Id(EntityType::Primitive, 8);
	const EntitySyntaxId Storage::f32Id(EntityType::Primitive, 9);
	const EntitySyntaxId Storage::f64Id(EntityType::Primitive, 10);
	const EntitySyntaxId Storage::boolId(EntityType::Primitive, 11);
	const EntitySyntaxId Storage::charId(EntityType::Primitive, 12);
	const EntitySyntaxId Storage::stringId(EntityType::Primitive, 13);

	Array<Primitive> primitives(14);
	Pool<PackageSyntax> packages(10'000);
	Pool<StructSyntax> structs(100'000);
	Pool<FunctionSyntax> functions(1'000'000);
	Pool<VariableSyntax> variables(10'000'000);
	Pool<ParameterSyntax> parameters(10'000'000);
	Pool<AdditiveExpressionSyntax> additiveExpressions(100'000'000);
	Pool<AssignmentExpressionSyntax> assignmentExpressions(100'000'000);
	Pool<BitwiseAndExpressionSyntax> bitwiseAndExpressions(100'000'000);
	Pool<BitwiseOrExpressionSyntax> bitwiseOrExpressions(100'000'000);
	Pool<BitwiseXorExpressionSyntax> bitwiseXorExpressions(100'000'000);
	Pool<BlockSyntax> blockExpressions(100'000'000);
	Pool<BooleanAndExpressionSyntax> booleanAndExpressions(100'000'000);
	Pool<BooleanOrExpressionSyntax> booleanOrExpressions(100'000'000);
	Pool<CallExpressionSyntax> callExpressions(100'000'000);
	Pool<ConditionalExpressionSyntax> conditionalExpressions(100'000'000);
	Pool<EqualityExpressionSyntax> equalityExpressions(100'000'000);
	Pool<IdentifierExpressionSyntax> identifierExpressions(100'000'000);
	// Pool<IfExpressionSyntax> ifExpressions(100'000'000);
	Pool<SubscriptExpressionSyntax> subscriptExpressions(100'000'000);
	Pool<MemberAccessExpressionSyntax> memberAccessExpressions(100'000'000);
	Pool<MultiplicativeExpressionSyntax> multiplicativeExpressions(100'000'000);
	Pool<PrefixExpressionSyntax> prefixExpressions(100'000'000);
	Pool<RelationalExpressionSyntax> relationalExpressions(100'000'000);
	Pool<ShiftExpressionSyntax> shiftExpressions(100'000'000);
	Pool<DeclarationStatementSyntax> declarationStatements(10'000'000);
	Pool<ExpressionStatementSyntax> expressionStatements(10'000'000);
	Pool<JumpStatementSyntax> jumpStatements(1'000'000);
	Pool<BoolLiteralSyntax> boolLiterals(1'000'000);
	Pool<CharLiteralSyntax> charLiterals(1'000'000);
	Pool<FloatLiteralSyntax> floatLiterals(1'000'000);
	Pool<IntegerLiteralSyntax> integerLiterals(1'000'000);
	Pool<StringLiteralSyntax> stringLiterals(1'000'000);

	void Storage::initialize()
	{
		primitives.push({ "void", PrimitiveType::Void, 0 });
		primitives.push({ "u8", PrimitiveType::UnsignedInteger, 1 });
		primitives.push({ "u16", PrimitiveType::UnsignedInteger, 2 });
		primitives.push({ "u32", PrimitiveType::UnsignedInteger, 4 });
		primitives.push({ "u64", PrimitiveType::UnsignedInteger, 8 });
		primitives.push({ "i8", PrimitiveType::SignedInteger, 1 });
		primitives.push({ "i16", PrimitiveType::SignedInteger, 2 });
		primitives.push({ "i32", PrimitiveType::SignedInteger, 4 });
		primitives.push({ "i64", PrimitiveType::SignedInteger, 8 });
		primitives.push({ "f32", PrimitiveType::FloatingPoint, 4 });
		primitives.push({ "f64", PrimitiveType::FloatingPoint, 8 });
		primitives.push({ "bool", PrimitiveType::Boolean, 1 });
		primitives.push({ "char", PrimitiveType::Character, 1 });
		primitives.push({ "string", PrimitiveType::String, 0 });
	}

	EntitySyntaxId Storage::add(PackageSyntax&& value)
	{
		usize index = packages.add(std::move(value));

		return EntitySyntaxId(EntityType::PackageSyntax, index);
	}

	EntitySyntaxId Storage::add(StructSyntax&& value)
	{
		usize index = structs.add(std::move(value));
		
		return EntitySyntaxId(EntityType::StructSyntax, index);
	}

	EntitySyntaxId Storage::add(FunctionSyntax&& value)
	{
		usize index = functions.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Function, index);
	}

	EntitySyntaxId Storage::add(VariableSyntax&& value)
	{
		usize index = variables.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Variable, index);
	}

	EntitySyntaxId Storage::add(ParameterSyntax&& value)
	{
		usize index = parameters.add(std::move(value));

		return EntitySyntaxId(EntityType::ParameterSyntax, index);
	}

	ExpressionSyntaxId Storage::add(AdditiveExpressionSyntax&& value)
	{
		auto index = additiveExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Additive, index);
	}

	ExpressionSyntaxId Storage::add(AssignmentExpressionSyntax&& value)
	{
		auto index = assignmentExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Assignment, index);
	}

	ExpressionSyntaxId Storage::add(BitwiseAndExpressionSyntax&& value)
	{
		auto index = bitwiseAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseAnd, index);
	}

	ExpressionSyntaxId Storage::add(BitwiseOrExpressionSyntax&& value)
	{
		auto index = bitwiseOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseOr, index);
	}

	ExpressionSyntaxId Storage::add(BitwiseXorExpressionSyntax&& value)
	{
		auto index = bitwiseXorExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseXor, index);
	}

	ExpressionSyntaxId Storage::add(BlockSyntax&& value)
	{
		auto index = blockExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Block, index);
	}

	ExpressionSyntaxId Storage::add(BooleanAndExpressionSyntax&& value)
	{
		auto index = booleanAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanAnd, index);
	}

	ExpressionSyntaxId Storage::add(BooleanOrExpressionSyntax&& value)
	{
		auto index = booleanOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanOr, index);
	}

	ExpressionSyntaxId Storage::add(CallExpressionSyntax&& value)
	{
		auto index = callExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Call, index);
	}

	ExpressionSyntaxId Storage::add(ConditionalExpressionSyntax&& value)
	{
		auto index = conditionalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Conditional, index);
	}

	ExpressionSyntaxId Storage::add(EqualityExpressionSyntax&& value)
	{
		auto index = equalityExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Equality, index);
	}

	ExpressionSyntaxId Storage::add(IdentifierExpressionSyntax&& value)
	{
		auto index = identifierExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IdentifierExpressionSyntax, index);
	}

	// ExpressionSyntaxId Storage::add(IfExpressionSyntax&& value)
	// {
	// 	auto index = ifExpressions.add(std::move(value));

	// 	return ExpressionSyntaxId(ExpressionType::If, index);
	// }

	ExpressionSyntaxId Storage::add(SubscriptExpressionSyntax&& value)
	{
		auto index = subscriptExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Subscript, index);
	}

	ExpressionSyntaxId Storage::add(MemberAccessExpressionSyntax&& value)
	{
		auto index = memberAccessExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::MemberAccessExpressionSyntax, index);
	}

	ExpressionSyntaxId Storage::add(MultiplicativeExpressionSyntax&& value)
	{
		auto index = multiplicativeExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Multiplicative, index);
	}

	ExpressionSyntaxId Storage::add(PrefixExpressionSyntax&& value)
	{
		auto index = prefixExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::PrefixExpressionSyntax, index);
	}

	ExpressionSyntaxId Storage::add(RelationalExpressionSyntax&& value)
	{
		auto index = relationalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Relational, index);
	}

	ExpressionSyntaxId Storage::add(ShiftExpressionSyntax&& value)
	{
		auto index = shiftExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Shift, index);
	}

	ExpressionSyntaxId Storage::add(BoolLiteralSyntax&& value)
	{
		auto index = boolLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BoolLiteralSyntax, index);
	}

	ExpressionSyntaxId Storage::add(CharLiteralSyntax&& value)
	{
		auto index = charLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::CharLiteralSyntax, index);
	}

	ExpressionSyntaxId Storage::add(FloatLiteralSyntax&& value)
	{
		auto index = floatLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::FloatLiteralSyntax, index);
	}

	ExpressionSyntaxId Storage::add(IntegerLiteralSyntax&& value)
	{
		auto index = integerLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IntegerLiteralSyntax, index);
	}

	ExpressionSyntaxId Storage::add(StringLiteralSyntax&& value)
	{
		auto index = stringLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::StringLiteralSyntax, index);
	}

	StatementSyntaxId Storage::add(DeclarationStatementSyntax&& value)
	{
		auto index = declarationStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::DeclarationStatementSyntax, index);
	}

	StatementSyntaxId Storage::add(ExpressionStatementSyntax&& value)
	{
		auto index = expressionStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::ExpressionSyntax, index);
	}

	StatementSyntaxId Storage::add(JumpStatementSyntax&& value)
	{
		auto index = jumpStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::Jump, index);
	}

	EntitySyntax& Storage::get(const EntitySyntaxId& id)
	{
		switch (id.type())
		{
			case EntityType::PackageSyntax:
				return packages[id.index()];

			case EntityType::StructSyntax:
				return structs[id.index()];

			case EntityType::Primitive:
				return primitives[id.index()];

			case EntityType::Function:
				return functions[id.index()];
				
			case EntityType::Variable:
				return variables[id.index()];

			case EntityType::ParameterSyntax:
				return parameters[id.index()];

			default:
				break;
		}
		
		exitWithError("Unable to get entity of type: $", (int)id.type());
	}

	ExpressionSyntax& Storage::get(const ExpressionSyntaxId& id)
	{
		switch (id.type())
		{
			case ExpressionType::Additive:
				return additiveExpressions[id.index()];

			case ExpressionType::Assignment:
				return assignmentExpressions[id.index()];

			case ExpressionType::BitwiseAnd:
				return bitwiseAndExpressions[id.index()];

			case ExpressionType::BitwiseOr:
				return bitwiseOrExpressions[id.index()];

			case ExpressionType::BitwiseXor:
				return bitwiseXorExpressions[id.index()];

			case ExpressionType::Block:
				return blockExpressions[id.index()];

			case ExpressionType::BooleanAnd:
				return booleanAndExpressions[id.index()];

			case ExpressionType::BooleanOr:
				return booleanOrExpressions[id.index()];

			case ExpressionType::Call:
				return callExpressions[id.index()];

			case ExpressionType::Conditional:
				return conditionalExpressions[id.index()];

			case ExpressionType::Equality:
				return equalityExpressions[id.index()];

			case ExpressionType::IdentifierExpressionSyntax:
				return identifierExpressions[id.index()];

			case ExpressionType::If:
				// TODO: Implemente get for If
				break;
				// return ifExpressions[id.index()];

			case ExpressionType::Subscript:
				return subscriptExpressions[id.index()];

			case ExpressionType::MemberAccessExpressionSyntax:
				return memberAccessExpressions[id.index()];

			case ExpressionType::Multiplicative:
				return multiplicativeExpressions[id.index()];

			case ExpressionType::PrefixExpressionSyntax:
				return prefixExpressions[id.index()];

			case ExpressionType::Relational:
				return relationalExpressions[id.index()];

			case ExpressionType::Shift:
				return shiftExpressions[id.index()];

			case ExpressionType::BoolLiteralSyntax:
				return boolLiterals[id.index()];
				
			case ExpressionType::CharLiteralSyntax:
				return charLiterals[id.index()];
				
			case ExpressionType::FloatLiteralSyntax:
				return floatLiterals[id.index()];
				
			case ExpressionType::IntegerLiteralSyntax:
				return integerLiterals[id.index()];
				
			case ExpressionType::StringLiteralSyntax:
				return stringLiterals[id.index()];
				
			default:
				break;
		}

		exitWithError("Unable to get ExpressionSyntax of type: $", (int)id.type());
	}

	StatementSyntax& Storage::get(const StatementSyntaxId& id)
	{
		switch (id.type())
		{
			case StatementType::DeclarationStatementSyntax:
				return declarationStatements[id.index()];

			case StatementType::ExpressionSyntax:
				return expressionStatements[id.index()];

			case StatementType::Jump:
				return jumpStatements[id.index()];

			default:
				break;
		}

		exitWithError("Unable to get Statement of type: $", (int)id.type());
	}

	PackageSyntax& Storage::getPackage(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::PackageSyntax);

		return packages[id.index()];
	}

	StructSyntax& Storage::getStruct(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::StructSyntax);

		return structs[id.index()];
	}

	FunctionSyntax& Storage::getFunction(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::Function);

		return functions[id.index()];
	}

	VariableSyntax& Storage::getVariable(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::Variable);

		return variables[id.index()];
	}

	ParameterSyntax& Storage::getParameter(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::ParameterSyntax);

		return parameters[id.index()];
	}

	EntitySyntaxId Storage::getId(FunctionSyntax& value)
	{
		auto index = functions.getIndex(&value);
		auto id = EntitySyntaxId(EntityType::Function, index);

		return id;
	}

	EntitySyntaxId Storage::getId(PackageSyntax& value)
	{
		auto index = packages.getIndex(&value);
		auto id = EntitySyntaxId(EntityType::PackageSyntax, index);

		return id;
	}

	void Storage::declarePrimitives(Table<String, EntitySyntaxId>& globalSymbols)
	{
		usize index = 0;

		for (const auto& primitive: primitives)
		{
			globalSymbols.emplace(primitive.identifier(), EntitySyntaxId { EntityType::Primitive, index });
			
			index += 1;
		}
	}

	usize Storage::getGlobalCount()
	{
		return packages.count() + structs.count() + functions.count();
	}
}