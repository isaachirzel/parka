#include "parka/ast/Package.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Entity.hpp"

namespace parka
{
	PackageSyntax::PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages) :
	_name(std::move(identifier)),
	_modules(std::move(modules)),
	_packages(std::move(packages)),
	_symbols(),
	_parent(nullptr),
	_context(nullptr)
	{}

	PackageContext::PackageContext(String&& symbol, Array<PackageContext*> packages, Array<FunctionContext*>&& functions, Array<StructContext*>&& structs) :
	_symbol(std::move(symbol)),
	_packages(std::move(packages)),
	_functions(std::move(functions)),
	_structs(std::move(structs))
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

		auto *context = new PackageContext(getSymbol(), std::move(packages), std::move(functions), std::move(structs));

		return context;
	}

	bool PackageSyntax::declare(EntitySyntax& entity)
	{
		// TODO: Invalidate symbol on failure, better error
		const auto& identifier = entity.name();
		auto result = _symbols.insert(identifier, &entity);

		if (!result)
		{
			// TODO: Show previous
			log::error("Name `$` is already declared in this package.", identifier);
		}

		return result;
	}

	bool PackageSyntax::declareSelf(PackageSyntax *parent)
	{
		// TODO: Actual error checking
		const auto isGlobalPackage = parent == nullptr;

		if (isGlobalPackage)
		{
			for (auto *primitive : Primitive::primitives)
			{
				_symbols.insert(primitive->name(), primitive);
			}
		}
		else
		{
			_parent = parent;
			_symbols.insert(_name, this);
		}

		for (auto& mod : _modules)
		{
			for (auto *strct : mod.structs())
				strct->declareSelf(*this);

			for (auto *function : mod.functions())
				function->declareSelf(*this);
		}

		for (auto *package : _packages)
			package->declareSelf(this);

		return true;
	}

	EntityEntry *PackageSyntax::findInitial(const Identifier& identifier)
	{
		const auto& name = identifier.text();
		auto *package = this;

		do
		{
			auto *entry = package->find(identifier);

			if (entry != nullptr)
				return entry;

			if (package->name() == name)
				return package;

			package = package->_parent;
		}
		while (package != nullptr);

		return nullptr;
	}

	EntityEntry *PackageSyntax::findAbsolute(const Identifier& identifier)
	{
		auto *package = this;
		auto *parent = _parent;
		
		while (parent != nullptr)
		{
			package = parent;
			parent = package->_parent;
		}

		assert(package->name().empty() && "Package with no parent must be the global package");

		auto *entry = package->find(identifier);

		return entry;
	}

	EntityEntry *PackageSyntax::find(const Identifier& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	EntityContext *PackageSyntax::resolve(const QualifiedIdentifier& qualifiedIdentifier)
	{
		// TODO: Optimize absolute package
		const auto& first = qualifiedIdentifier[0];
		auto *entry = qualifiedIdentifier.isAbsolute()
			? findInitial(first)
			: findAbsolute(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = dynamic_cast<SymbolTable*>(entry);

			if (table == nullptr)
			{
				log::error("Unable to resolve $ in $ $.", identifier, entry->entityType(), entry->name());
				return nullptr;
			}

			entry = table->find(identifier);
		}

		if (entry != nullptr)
			return entry->context();

		// TODO: Use index to shorten the symbol so it is more specific what could not be found
		log::error("Unable to find $ in this scope.", qualifiedIdentifier);

		return nullptr;
	}

	String PackageSyntax::getSymbol() const
	{
		if (_parent == nullptr)
		{
			auto symbol = String();

			symbol.reserve(128);
			symbol += _name;

			return symbol;
		}

		auto symbol = _parent->getSymbol();

		symbol += "::";
		symbol += _name;
		
		return symbol;
	}

	std::ostream& operator<<(std::ostream& out, const PackageSyntax& syntax)
	{
		auto indent = Indent(out);

		out << indent;

		if (syntax._name.empty())
		{
			out << "global\n";
		}
		else
		{
			out << "package `" << syntax._name << "`\n";
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
