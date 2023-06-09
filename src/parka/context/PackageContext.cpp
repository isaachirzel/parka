#include "parka/context/PackageContext.hpp"
#include "parka/context/FunctionContext.hpp"
#include "parka/context/StructContext.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"

namespace parka
{
	const PackageContext *PackageContext::validate(PackageSymbolTable& symbolTable)
	{
		auto success = true;
		// const auto& packageSyntax = symbolTable.packageId().getPackage();
		auto functions = Array<EntityContextId>();
		auto structs = Array<EntityContextId>();

		for (auto& tuple : symbolTable.symbols())
		{
			auto& entry = tuple.value();
			const auto& syntax = entry.syntax();
			const auto& type = syntax.type();
			const auto *context = (const EntityContext*)nullptr;

			switch (type)
			{
				case EntityType::Package:
					context = PackageContext::validate(entry.packageSymbolTable());
					break;

				case EntityType::Struct:
					// TODO: Implement struct support
					// contextId = StructContext::validate(entry.structSymbolTable());
					break;

				case EntityType::Primitive:
					context = (const Primitive*)&entry.syntax();
					break;

				case EntityType::Function:
				{
					auto functionSymbolTable = FunctionSymbolTable((const FunctionSyntax&)syntax, symbolTable);

					context = FunctionContext::validate(functionSymbolTable);
					break;
				}

				default:
					log::fatal("Unable to validate package SymbolTableEntry of type: $", type);
					break;
			}

			if (!context)
			{
				success = false;
				continue;
			}
			
			entry.setContext(*context);
		}

		if (!success)
			return {};

		auto result = PackageContext(std::move(functions), std::move(structs));
		auto& context = EntityContext::create(std::move(result));

		return (const PackageContext*)&context;
	}
}
