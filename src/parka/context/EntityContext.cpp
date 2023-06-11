// #include "parka/log/Log.hpp"

// namespace parka
// {
// 	// static Pool<PackageContext> packages(1'000);
// 	// static Pool<StructContext> structs(100'000);
// 	// static Pool<FunctionContext> functions(1'000'000);
// 	// static Pool<VariableContext> variables(10'000'000);
// 	// static Pool<ParameterContext> parameters(10'000'000);

// 	const EntityContext& EntityContext::create(EntityContext&& context)
// 	{
// 		auto type = context.entityType();
	
// 		switch (type)
// 		{
// 			case EntityType::Package:
// 				return packages.add(std::move((PackageContext&)context));

// 			case EntityType::Struct:
// 				return structs.add(std::move((StructContext&)context));

// 			case EntityType::Function:
// 				return functions.add(std::move((FunctionContext&)context));

// 			// case EntityType::Variable:
// 			// 	return variables.add(std::move((VariableContext&)context));

// 			// case EntityType::Parameter:
// 			// 	return parameters.add(std::move((ParameterContext&)context));

// 			default:
// 				break;
// 		}

// 		log::fatal("Unable to create EntityContext with type: $", type);
// 	}

// 	static usize getEntityContextIndex(const EntityType type, const EntityContext& context)
// 	{
// 		switch (type)
// 		{
// 			case EntityType::Package:
// 				return packages.indexFor((const PackageContext*)&context);
				
// 			case EntityType::Struct:
// 				return structs.indexFor((const StructContext*)&context);

// 			case EntityType::Primitive:
// 			{
// 				const auto *ptr = (const Primitive*)&context;
// 				return Primitive::primitives.indexFor(&ptr);
// 			}
				
// 			case EntityType::Function:
// 				return functions.indexFor((const FunctionContext*)&functions);

// 			// case EntityType::Variable:
// 			// 	return functions.indexFor((const VariableContext*)&variables);

// 			// case EntityType::Parameter:
// 			// 	return parameters.indexFor((const ParameterContext*)&parameters);

// 			default:
// 				break;
// 		}

// 		log::fatal("Unable to get Id for EntityContext with type: $", type);
// 	}

// 	EntityContextId EntityContext::idFor(const EntityContext& context)
// 	{
// 		auto type = context.type();
// 		auto index = getEntityContextIndex(type, context);

// 		return EntityContextId(type, index);
// 	}
// }