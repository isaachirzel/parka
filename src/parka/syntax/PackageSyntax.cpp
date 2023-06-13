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

		for (auto& mod : _modules)
		{
			for (auto *syntax : mod.functions())
			{
				auto *context = syntax->validate();

				if (!context)
				{
					success = false;
					continue;
				}

				functions.push(context);
			}

			// for (auto *syntax : mod.structs())
			// {
			// 	auto *context = syntax->validate(*this);

			// 	if (!context)
			// 		continue;

			// 	structs.push(context);
			// }
		}

		for (auto *syntax : _packages)
		{
			auto *context = syntax->validate();

			if (!context)
			{
				success = false;
				continue;
			}

			packages.push(context);
		}

		if (!success)
			return {};

		auto *context = new PackageContext(std::move(packages), std::move(functions), std::move(structs));

		return context;
	}

	bool PackageSyntax::declareEntity(const EntitySyntax& entity)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entity, *this);
		const auto& identifier = entity.identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			log::error("Name `$` is already declared in this package.", identifier);

		return result;
	}

	void PackageSyntax::declare(PackageSyntax *parent)
	{
		_parent = parent;

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
				declareEntity(*strct);

			for (const auto *function : mod.functions())
				declareEntity(*function);
		}

		for (const auto *package : _packages)
			declareEntity(*package);
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
		auto result = _symbols.find(identifier.text());

		if (!result)
		{
			log::error("Unable to find symbol `$`.", identifier);
			return {};
		}

		
		
		return result->context();
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
