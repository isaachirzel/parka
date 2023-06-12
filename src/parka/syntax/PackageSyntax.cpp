#include "parka/syntax/PackageSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"

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

	PackageContext *PackageSyntax::validate()
	{
		auto success = true;
		auto packages = Array<PackageContext*>();
		auto functions = Array<FunctionContext*>();
		auto structs = Array<StructContext*>();

		for (auto& tuple : _symbols)
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
				// 	context = syntax.validate(entry.PackageSyntax());
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

	void PackageSyntax::declare()
	{
		const auto isGlobalPackage = _parent == nullptr;

		if (isGlobalPackage)
		{
			for (const auto *primitive : Primitive::primitives)
			{
				_symbols.insert(primitive->identifier(), SymbolTableEntry(*primitive, *this));
			}
		}

		for (const auto& mod : _modules)
		{
			for (const auto *strct : mod.structs())
				declare(*strct);

			for (const auto *function : mod.functions())
				declare(*function);
		}

		for (const auto *package : _packages)
			declare(*package);
	}

	bool PackageSyntax::declare(const EntitySyntax& entity)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entity, *this);
		const auto& identifier = entity.identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			log::error("Name `$` is already declared in this package.", identifier);

		return result;
	}

	SymbolTableEntry *PackageSyntax::findEntry(const QualifiedIdentifier& identifier, usize index)
	{
		auto& part = identifier[index];
		auto *result = resolve(part);

		if (!result)
		{
			if (_parent)
				result = _parent->resolve(part);

			if (!result)
			{
				// TODO: Output package symbol, entity type and reference highlight
				log::error("Unable to find `$` in package `$`.", part.text(), _identifier);
				
				return nullptr;
			}
		}

		return nullptr;
	}

	const EntityContext *PackageSyntax::resolve(const Identifier& identifier)
	{
		// TODO: Confirm this makes sense. I'm not sure if resolving single identifiers should always do
		// this or if it should seek upwards at times
		const auto *result = _symbols.find(identifier.text());

		if (!result)
			return {};
			
		if (result->context())
			return result->context();

		log::notImplemented(here());
		// return &result->syntax();
	}

	const EntityContext *PackageSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		// TODO: Make this logic work
		const auto *result = findEntry(identifier, 0);

		if (!result)
			return {};

		if (result->context())
			return result->context();

		log::notImplemented(here());
	}

	std::ostream& operator<<(std::ostream& out, const PackageSyntax& package)
	{
		// TODO: Implement printing other packages
		auto indent = Indent(out);
		const auto& identifier = package._identifier;

		out << (identifier.length() > 0 ? identifier : "Global Scope") << ":\n";

		for (const auto& entry : package._symbols)
		{
			out << indent << entry.value();
		}

		return out;
	}
}
