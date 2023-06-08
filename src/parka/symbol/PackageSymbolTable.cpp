#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	PackageSymbolTable::PackageSymbolTable(const PackageSyntax& syntax, const SymbolTable *parent) :
	_syntax(syntax),
	_symbols(), // TODO: pre-reserve symbol count
	_parent(parent)
	{
		const auto isGlobalPackage = parent == nullptr;

		if (isGlobalPackage)
		{
			for (const auto *primitive : Primitive::primitives)
			{
				_symbols.insert(primitive->identifier(), SymbolTableEntry(*primitive, *this));
			}
		}

		for (const auto& mod : _syntax.modules())
		{
			for (const auto *strct : mod.structs())
				declare(*strct);

			for (const auto *function : mod.functions())
				declare(*function);
		}

		for (const auto *package : syntax.packages())
			declare(*package);
	}

	bool PackageSymbolTable::declare(const EntitySyntax& entity)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entity,  *this);
		const auto& identifier = entity.identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			log::error("Name `$` is already declared in this package.", identifier);

		return result;
	}

	const SymbolTableEntry *PackageSymbolTable::findEntry(const QualifiedIdentifier& identifier, usize index) const
	{
		auto& part = identifier[index];
		auto result = resolve(part);

		if (!result)
		{
			if (_parent)
				result = _parent->resolve(part);

			if (!result)
			{
				// TODO: Output package symbol, entity type and reference highlight
				log::error("Unable to find `$` in package `$`.", part.text(), _syntax.identifier());
				
				return nullptr;
			}
		}

		return nullptr;
	}

	const EntitySyntax *PackageSymbolTable::resolve(const Identifier& identifier) const
	{
		// TODO: Confirm this makes sense. I'm not sure if resolving single identifiers should always do
		// this or if it should seek upwards at times
		const auto *result = _symbols.find(identifier.text());

		if (!result)
			return {};
			
		return &result->syntax();
	}

	const EntitySyntax *PackageSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		// TODO: Make this logic work
		const auto *entry = findEntry(identifier, 0);

		if (!entry)
			return {};

		return &entry->syntax();
	}

	std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& symbols)
	{
		// TODO: Implement printing other packages
		auto indent = Indent(out);
		const auto& identifier = symbols.syntax().identifier();

		out << (identifier.length() > 0 ? identifier : "Global Scope") << ":\n";

		for (const auto& entry : symbols._symbols)
		{
			out << indent << entry.value();
		}

		return out;
	}
}
