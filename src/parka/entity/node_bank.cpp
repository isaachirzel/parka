#include "parka/entity/node_bank.hpp"

#include "parka/symbol/symbol_table.hpp"
#include "parka/util/array.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/util/pool.hpp"

Array<Primitive> _primitives =
{
	{ "void", PRIMITIVE_VOID, 0 },
	{ "u8", PRIMITIVE_UNSIGNED_INTEGER, 1 },
	{ "u16", PRIMITIVE_UNSIGNED_INTEGER, 2 },
	{ "u32", PRIMITIVE_UNSIGNED_INTEGER, 4 },
	{ "u64", PRIMITIVE_UNSIGNED_INTEGER, 8 },
	{ "i8", PRIMITIVE_SIGNED_INTEGER, 1 },
	{ "i16", PRIMITIVE_SIGNED_INTEGER, 2 },
	{ "i32", PRIMITIVE_SIGNED_INTEGER, 4 },
	{ "i64", PRIMITIVE_SIGNED_INTEGER, 8 },
	{ "f32", PRIMITIVE_FLOATING_POINT, 4 },
	{ "f64", PRIMITIVE_FLOATING_POINT, 8 },
	{ "bool", PRIMITIVE_BOOLEAN, 1 },
	{ "char", PRIMITIVE_CHARACTER, 1 },
	{ "string", PRIMITIVE_STRING, 0 }
};
Pool<Package> _packages(10'000);
Pool<Struct> _structs(100'000);
Pool<Function> _functions(1'000'000);
Pool<Variable> _variables(10'000'000);
Pool<Parameter> _parameters(10'000'000);
Pool<AdditiveExpression> _additiveExpressions(100'000'000);
Pool<Assignment> _assignmentExpressions(100'000'000);
Pool<BitwiseAndExpression> _bitwiseAndExpressions(100'000'000);
Pool<BitwiseOrExpression> _bitwiseOrExpressions(100'000'000);
Pool<BitwiseXorExpression> _bitwiseXorExpressions(100'000'000);
Pool<Block> _blockExpressions(100'000'000);
Pool<BooleanAndExpression> _booleanAndExpressions(100'000'000);
Pool<BooleanOrExpression> _booleanOrExpressions(100'000'000);
Pool<CallExpression> _callExpressions(100'000'000);
Pool<ConditionalExpression> _conditionalExpressions(100'000'000);
Pool<EqualityExpression> _equalityExpressions(100'000'000);
Pool<Identifier> _identifierExpressions(100'000'000);
Pool<IfExpression> _ifExpressions(100'000'000);
Pool<IndexExpression> _subscriptExpressions(100'000'000);
Pool<MemberAccess> _memberAccessExpressions(100'000'000);
Pool<MultiplicativeExpression> _multiplicativeExpressions(100'000'000);
Pool<Prefix> _prefixExpressions(100'000'000);
Pool<RelationalExpression> _relationalExpressions(100'000'000);
Pool<BitShiftExpression> _shifExpressions(100'000'000);
Pool<Declaration> _declarationStatements(10'000'000);
Pool<ExpressionStatement> _expressionStatements(10'000'000);
Pool<JumpStatement> _jumpStatements(1'000'000);
Pool<BoolLiteral> _boolLiterals(1'000'000);
Pool<CharLiteral> _charLiterals(1'000'000);
Pool<FloatLiteral> _floatLiterals(1'000'000);
Pool<IntegerLiteral> _integerLiteral(1'000'000);
Pool<StringLiteral> _stringLiterals(1'000'000);

void NodeBank::declarePrimitives(Table<EntityId>& globalSymbols)
{
	usize index = 0;

	for (const auto& primitive: _primitives)
	{
		globalSymbols.emplace(primitive.symbol(), EntityId { EntityType::Primitive, index });
		index += 1;
	}
}

usize NodeBank::getGlobalCount()
{
	return _packages.count() + _structs.count() + _functions.count();
}
