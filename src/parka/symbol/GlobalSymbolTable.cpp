#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/SourceLocation.hpp"

namespace parka
{
	GlobalSymbolTable::GlobalSymbolTable(const SyntaxTree& syntaxTree)
	{
		for (const auto& mod : syntaxTree.modules())
		{
			for (const auto& structId : mod.structIds())
				declare(structId);

			for (const auto& functionId : mod.functionIds())
				declare(functionId);
		}

		for (const auto& packageId : syntaxTree.packageIds())
			declare(packageId);

		// TODO: imported extern packages
	}

	void GlobalSymbolTable::declare(const EntitySyntaxId& entityId)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entityId, *this);
		const auto& identifier = entityId->identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			log::error("Name `$` is already declared in global scope.", identifier);
	}

	Optional<EntitySyntaxId> GlobalSymbolTable::resolve(const Identifier&) const
	{
		log::notImplemented(here());
	}

	Optional<EntitySyntaxId> GlobalSymbolTable::resolve(const QualifiedIdentifier&) const
	{
		log::notImplemented(here());
	}

	std::ostream& operator<<(std::ostream& out, const GlobalSymbolTable& globalSymbols)
	{
		// TODO: Implement printing other packages
		auto indent = Indent(out);

		out << "global:\n";

		for (const auto& entry : globalSymbols._symbols)
		{
			out << indent << entry.value();
		}

		return out;
	}
}
