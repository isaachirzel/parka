#include "parka/ast/type/type.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/literal/literal.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/util/print.hpp"

const Type voidType = Type({ EntityType::Primitive, INDEX_VOID });
const Type i32Type = Type({ EntityType::Primitive, INDEX_I32 });

String Type::getName() const
{
	auto& entity = NodeBank::get(_entityId);

	return entity.symbol();
}

bool Type::canConvertTo(const Type& to)
{
	return _entityId == to.entityId();
}
