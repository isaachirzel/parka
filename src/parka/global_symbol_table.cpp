#include "parka/global_symbol_table.hpp"

#include <cstdlib>
#include <cassert>
#include <cstring>

const Array<Primitive> primitives =
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

GlobalEntityTable::GlobalEntityTable() :
_packages(10'000),
_structs(100'000),
_functions(100'000),
_variables(1'000'000),
_parameters(1'000'000)
{
	usize index = 0;

	for (auto& primitive : primitives)
	{
		auto context = EntityContext(primitive);
		
		context.validate();

		_entities.emplace(std::move(context));

		index += 1;
	}
}

Ref<EntityContext> GlobalEntityTable::resolve(const Scope& scope, const Token& token)
{
	// TODO: Optimize
	auto identifier = token.text();

	EntityContext *symbol = NULL;

	usize i = scope.count();

	do
	{
		i -= 1;

		String symbol = scope.createSymbolN(identifier, i);
		auto iter = _entities.find(symbol);

		if (iter != _entities.end())
			return iter->second;
	}
	while (i > 0);

	printTokenError(token, "Unable to find '%s' in this scope.", identifier.c_str());

	return {};
}

bool GlobalEntityTable::declare(EntityId id)
{
	// TODO: Optimize to not do two lookups
	// TODO: Add tokens for highlighting
	auto& entity = getEntity(id);
	const auto& symbol = entity.symbol();
	auto iter = _entities.find(symbol);

	if (iter != _entities.end())
	{
		
		auto& context = iter->second;
		auto& previous = context.entity();

		printError( "'%s' is already declared in this package.", symbol.c_str());
		// printNote(previousName, "Previous declaration here.");

		context.invalidate();

		return false;
	}

	_entities.emplace(symbol, EntityContext(entity, id));

	return true;
}



Ref<EntityContext> GlobalEntityTable::resolve(const Scope& scope, const Token& token)
{
	char *identifier = tokenGetText(token);
	EntityContext *symbol = symbolTableResolveIdentifier(scope, identifier);

	if (!symbol)
		printTokenError(token, "Unable to find '%s' in this scope.", identifier);

	deallocate(identifier);

	return symbol;
}

EntityId addEntity(

const String& GlobalEntityTable::getSymbolKey(EntityType type, usize index)
{
	switch (type)
	{
		case EntityType::Package:
		{
			auto& package = getPackage(index);

			return package.symbol();
		}

		case EntityType::Struct:
		{
			auto& strct = getStruct(index);

			return strct.symbol();
		}

		case EntityType::Primitive:
		{
			auto& primitive = getPrimitive(index);

			return primitive.symbol();
		}

		case EntityType::Function:
		{
			auto& function = symbolTableGetFunction(index);

			return function.symbol();
		}

		case EntityType::Variable:
		{
			auto& variable = getVariable(index);

			return variable.symbol();
		}

		case EntityType::Parameter:
		{
			auto& parameter = getParameter(index);

			return parameter.symbol();
		}
	}
}
