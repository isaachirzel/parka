#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/util/Print.hpp"

#include <functional>

namespace parka
{
	const EntitySyntaxId EntitySyntaxId::voidId(EntityType::Primitive, 0);
	const EntitySyntaxId EntitySyntaxId::u8Id(EntityType::Primitive, 1);
	const EntitySyntaxId EntitySyntaxId::u16Id(EntityType::Primitive, 2);
	const EntitySyntaxId EntitySyntaxId::u32Id(EntityType::Primitive, 3);
	const EntitySyntaxId EntitySyntaxId::u64Id(EntityType::Primitive, 4);
	const EntitySyntaxId EntitySyntaxId::i8Id(EntityType::Primitive, 5);
	const EntitySyntaxId EntitySyntaxId::i16Id(EntityType::Primitive, 6);
	const EntitySyntaxId EntitySyntaxId::i32Id(EntityType::Primitive, 7);
	const EntitySyntaxId EntitySyntaxId::i64Id(EntityType::Primitive, 8);
	const EntitySyntaxId EntitySyntaxId::f32Id(EntityType::Primitive, 9);
	const EntitySyntaxId EntitySyntaxId::f64Id(EntityType::Primitive, 10);
	const EntitySyntaxId EntitySyntaxId::boolId(EntityType::Primitive, 11);
	const EntitySyntaxId EntitySyntaxId::charId(EntityType::Primitive, 12);
	const EntitySyntaxId EntitySyntaxId::stringId(EntityType::Primitive, 13);

	static const View<Primitive> primitives(Primitive::primitives, Primitive::primitiveCount);
	static Pool<PackageSyntax> packages(10'000);
	static Pool<StructSyntax> structs(100'000);
	static Pool<FunctionSyntax> functions(1'000'000);
	static Pool<VariableSyntax> variables(10'000'000);
	static Pool<ParameterSyntax> parameters(10'000'000);

	EntitySyntaxId EntitySyntaxId::create(PackageSyntax&& value)
	{
		usize index = packages.add(std::move(value));

		return EntitySyntaxId(EntityType::Package, index);
	}

	EntitySyntaxId EntitySyntaxId::create(StructSyntax&& value)
	{
		usize index = structs.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Struct, index);
	}

	EntitySyntaxId EntitySyntaxId::create(FunctionSyntax&& value)
	{
		usize index = functions.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Function, index);
	}

	EntitySyntaxId EntitySyntaxId::create(VariableSyntax&& value)
	{
		usize index = variables.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Variable, index);
	}

	EntitySyntaxId EntitySyntaxId::create(ParameterSyntax&& value)
	{
		usize index = parameters.add(std::move(value));

		return EntitySyntaxId(EntityType::Parameter, index);
	}

	EntitySyntaxId EntitySyntaxId::getFor(const PackageSyntax& package)
	{
		auto index = packages.getIndex(&package);
		auto id = EntitySyntaxId(EntityType::Package, index);

		return id;
	}

	EntitySyntaxId EntitySyntaxId::getFor(const FunctionSyntax& function)
	{
		auto index = functions.getIndex(&function);
		auto id = EntitySyntaxId(EntityType::Function, index);

		return id;
	}

	const PackageSyntax& EntitySyntaxId::getPackage() const
	{
		assert(_type == EntityType::Package);

		return packages[_index];
	}

	const StructSyntax& EntitySyntaxId::getStruct() const
	{
		assert(_type == EntityType::Struct);

		return structs[_index];
	}

	const FunctionSyntax& EntitySyntaxId::getFunction() const
	{
		assert(_type == EntityType::Function);

		return functions[_index];
	}

	const VariableSyntax& EntitySyntaxId::getVariable() const
	{
		assert(_type == EntityType::Variable);

		return variables[_index];
	}

	const ParameterSyntax& EntitySyntaxId::getParameter() const
	{
		assert(_type == EntityType::Parameter);

		return parameters[_index];
	}

	std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id)
	{

		out << id._type << "s[" << id._index << ']';

		return out;
	}

	bool EntitySyntaxId::operator==(const EntitySyntaxId& other) const
	{
		return _type == other._type && _index == other._index;
	}

	const EntitySyntax& EntitySyntaxId::operator*() const
	{
		switch (_type)
		{
			case EntityType::Package:
				return packages[_index];

			case EntityType::Struct:
				return structs[_index];

			case EntityType::Primitive:
				return Primitive::primitives[_index];

			case EntityType::Function:
				return functions[_index];
				
			case EntityType::Variable:
				return variables[_index];

			case EntityType::Parameter:
				return parameters[_index];

			default:
				break;
		}
		
		exitWithError("Unable to get entity of type: $", (int)_type);
	}

	const EntitySyntax *EntitySyntaxId::operator->() const
	{
		return &(*(*this));
	}
}

namespace std
{
	using namespace parka;

	usize hash<EntitySyntaxId>::operator()(const EntitySyntaxId& key) const
	{
		auto seed = (u64)key._index  | ((u64)key._type << 32);
		auto hash = std::hash<usize>{}(seed);

		return hash;
	}
}
