#include "parka/syntax/EntitySyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/util/Pool.hpp"

namespace parka
{
	static Pool<PackageSyntax> packages(1'000);
	static Pool<StructSyntax> structs(100'000);
	static Pool<FunctionSyntax> functions(1'000'000);
	static Pool<VariableSyntax> variables(10'000'000);
	static Pool<ParameterSyntax> parameters(10'000'000);
	
	const EntitySyntax& EntitySyntax::create(EntitySyntax&& syntax)
	{
		auto type = syntax.type();
	
		switch (type)
		{
			case EntityType::Package:
				return packages.add(std::move((PackageSyntax&)syntax));

			case EntityType::Struct:
				return structs.add(std::move((StructSyntax&)syntax));

			case EntityType::Function:
				return functions.add(std::move((FunctionSyntax&)syntax));

			case EntityType::Variable:
				return variables.add(std::move((VariableSyntax&)syntax));

			case EntityType::Parameter:
				return parameters.add(std::move((ParameterSyntax&)syntax));

			default:
				break;
		}

		log::fatal("Unable to create EntityContext with type: $", type);
	}

	static usize getEntitySyntaxIndex(const EntityType type, const EntitySyntax& syntax)
	{
		switch (type)
		{

			case EntityType::Package:
				return packages.indexFor((const PackageSyntax*)&syntax);
				
			case EntityType::Struct:
				return structs.indexFor((const StructSyntax*)&syntax);

			case EntityType::Primitive:
			{
				const auto *ptr = (const Primitive*)&syntax;
				return Primitive::primitives.indexFor(&ptr);
			}
				
			case EntityType::Function:
				return functions.indexFor((const FunctionSyntax*)&syntax);

			case EntityType::Variable:
				return variables.indexFor((const VariableSyntax*)&syntax);

			case EntityType::Parameter:
				return parameters.indexFor((const ParameterSyntax*)&syntax);

			default:
				break;
		}

		log::fatal("Unable to get Id for EntityContext with type: $", type);
	}

	EntitySyntaxId EntitySyntax::idFor(const EntitySyntax& syntax)
	{
		auto type = syntax.type();
		auto index = getEntitySyntaxIndex(type, syntax);

		return EntitySyntaxId(type, index);
	}
}