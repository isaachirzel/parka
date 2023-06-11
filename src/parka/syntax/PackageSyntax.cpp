#include "parka/syntax/PackageSyntax.hpp"
#include "parka/context/PackageContext.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	PackageSyntax::PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages) :
	_identifier(std::move(identifier)),
	_modules(std::move(modules)),
	_packages(std::move(packages))
	{}

	PackageSyntax *PackageSyntax::parse(const Directory& directory, const String& name)
	{
		// TODO: Add multithreading
		auto modules = Array<ModuleSyntax>(directory.files().length());
		auto packages = Array<PackageSyntax*>(directory.subdirectories().length());

		for (const auto& file : directory.files())
			modules.push(ModuleSyntax::parse(file));

		for (const auto& subdirectory : directory.subdirectories())
			packages.push(PackageSyntax::parse(subdirectory, subdirectory.name()));

		auto *syntax = new PackageSyntax(String(name), std::move(modules), std::move(packages));

		return syntax;
	}

	PackageContext *PackageSyntax::validate(SymbolTable& symbolTable)
	{
		assert(symbolTable.symbolTableType() == SymbolTableType::Package);

		auto& packageSymbolTable = static_cast<PackageSymbolTable&>(symbolTable);
		auto success = true;
		auto packages = Array<PackageContext*>();
		auto functions = Array<FunctionContext*>();
		auto structs = Array<StructContext*>();

		for (auto& tuple : packageSymbolTable.symbols())
		{
			auto& entry = tuple.value();
			const auto& syntax = entry.syntax();
			const auto& type = syntax.entityType();
			auto *context = (const EntityContext*)nullptr;

			switch (type)
			{
				// case EntityType::Package:
				// {
				// 	auto& package = (PackageSyntax&)*entry.syntax();
				// 	context = syntax.validate(entry.packageSymbolTable());
				// 	break;
				// }

				// case EntityType::Struct:
				// 	// TODO: Implement struct support
				// 	// contextId = StructContext::validate(entry.structSymbolTable());
				// 	break;

				// case EntityType::Primitive:
				// 	context = (Primitive*)&entry.syntax();
				// 	break;

				// case EntityType::Function:
				// {
				// 	auto functionSymbolTable = FunctionSymbolTable((const FunctionSyntax&)syntax, symbolTable);

				// 	context = FunctionContext::validate(functionSymbolTable);
				// 	break;
				// }

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

		auto *context = new PackageContext(std::move(packages), std::move(functions), std::move(structs));

		return context;
	}
}
