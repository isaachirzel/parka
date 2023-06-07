#include "parka/context/PackageContext.hpp"
#include "parka/context/FunctionContext.hpp"
#include "parka/context/StructContext.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<EntityContextId> PackageContext::validate(PackageSymbolTable& symbolTable)
	{
		auto success = true;
		// const auto& packageSyntax = symbolTable.packageId().getPackage();
		auto functionIds = Array<EntityContextId>();
		auto structIds = Array<EntityContextId>();

		for (auto& tuple : symbolTable.symbols())
		{
			auto& entry = tuple.value();
			const auto& type = entry.type();
			auto contextId = Optional<EntityContextId>();

			switch (type)
			{
				case EntityType::Package:
					contextId = PackageContext::validate(entry.packageSymbolTable());
					break;

				case EntityType::Struct:
					// TODO: Implement struct support
					// contextId = StructContext::validate(entry.structSymbolTable());
					break;

				case EntityType::Primitive:				
					contextId = EntityContextId::get(entry.syntaxId().getPrimitive());
					break;

				case EntityType::Function:
				{
					auto functionSymbolTable = FunctionSymbolTable(entry.syntaxId(), symbolTable);

					contextId = FunctionContext::validate(functionSymbolTable);
					break;
				}

				default:
					log::fatal("Unable to validate package SymbolTableEntry of type: $", type);
					break;
			}

			if (!contextId)
			{
				success = false;
				continue;
			}
			
			entry.contextId() = *contextId;
		}

		if (!success)
			return {};

		auto result = PackageContext(std::move(functionIds), std::move(structIds));
		auto contextId = EntityContextId::create(std::move(result));

		return contextId;
	}
}
