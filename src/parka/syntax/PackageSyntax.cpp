#include "parka/syntax/PackageSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/syntax/EntitySyntax.hpp"

namespace parka
{
	PackageSyntax::PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages) :
	_identifier(std::move(identifier)),
	_modules(std::move(modules)),
	_packages(std::move(packages)),
	_symbols(),
	_parent(nullptr),
	_context(nullptr)
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

	bool PackageSyntax::declareEntity(EntitySyntax& entity)
	{
		// TODO: Invalidate symbol on failure, better error
		const auto& identifier = entity.identifier();
		auto result = _symbols.insert(identifier, &entity);

		if (!result)
		{
			// TODO: Show previous
			log::error("Name `$` is already declared in this package.", identifier);
		}

		return result;
	}

	void PackageSyntax::declare(PackageSyntax *parent)
	{
		_parent = parent;

		const auto isGlobalPackage = _parent == nullptr;

		if (isGlobalPackage)
		{
			for (auto *primitive : Primitive::primitives)
			{
				_symbols.insert(primitive->identifier(), primitive);
			}
		}

		for (auto& mod : _modules)
		{
			for (auto *strct : mod.structs())
				declareEntity(*strct);

			for (auto *function : mod.functions())
				declareEntity(*function);
		}

		for (auto *package : _packages)
			declareEntity(*package);
	}

	// SymbolTableEntry *PackageSyntax::findEntry(const QualifiedIdentifier& identifier, usize index)
	// {
	// 	auto& part = identifier[index];
	// 	auto *result = resolve(part);

	// 	if (!result)
	// 	{
	// 		if (_parent)
	// 			result = _parent->resolve(part);

	// 		if (!result)
	// 		{
	// 			// TODO: Output package symbol, entity type and reference highlight
	// 			log::error("Unable to find `$` in package `$`.", part.text(), _identifier);
				
	// 			return nullptr;
	// 		}
	// 	}

	// 	return nullptr;
	// }

	EntitySyntax *PackageSyntax::resolve(const Identifier& identifier)
	{
		// TODO: Confirm this makes sense. I'm not sure if resolving single identifiers should always do
		// this or if it should seek upwards at times
		auto result = _symbols.find(identifier.text());

		if (!result)
		{
			log::error("Unable to find symbol `$`.", identifier);
			return nullptr;
		}

		return *result;
	}

	EntitySyntax *PackageSyntax::find(const String& key)
	{
		auto* iter = _symbols.find(key);

		if (iter)
			return *iter;

		auto *entity = this;

		do
		{
			if (entity->identifier() == key)
				return entity;

			entity = _parent;
		}
		while (entity != nullptr);

		return entity;
	}

	EntitySyntax *PackageSyntax::resolve(const QualifiedIdentifier& qualifiedIdentifier)
	{
		assert(qualifiedIdentifier.length() > 0);

		// TODO: Optimize absolute package
		const auto& first = qualifiedIdentifier[0];
		auto *entry = find(first.text());

		if (!entry)
		{
			log::error("Unable to find package `$`.", first);
			return nullptr;
		}

		auto *table = (SymbolTable*)nullptr;

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			const auto& identifier = qualifiedIdentifier[i];

			table = dynamic_cast<SymbolTable*>(entry);

			if (table == nullptr)
			{
				log::error("Unable to resolve member `$` of $ `$`.", identifier, entry->entityType(), entry->identifier());
				return nullptr;
			}

			entry = table->resolve(identifier);
		}

		return entry;
	}

	std::ostream& operator<<(std::ostream& out, const PackageSyntax& syntax)
	{
		auto indent = Indent(out);

		out << indent;

		if (syntax._identifier.empty())
		{
			out << "global\n";
		}
		else
		{
			out << "package `" << syntax._identifier << "`\n";
		}

		out << indent << "{\n";

		{
			auto subindent = Indent(out);

			out << subindent << "symbols\n";
			out << subindent << "{\n";

			{
				auto subsubindent = Indent(out);

				for (const auto& entry : syntax._symbols)
				{
					out << subsubindent << *entry.value() << '\n';
				}

			}

			out << subindent << "}\n\n";
		}

		for (const auto& mod : syntax._modules)
		{
			out << mod << '\n';
		}

		for (const auto *package : syntax._packages)
		{
			out << *package << '\n';
		}

		out << indent << "}";

		return out;
	}
}
