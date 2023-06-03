#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/SourceLocation.hpp"

namespace parka
{
	bool GlobalSymbolTable::declare(const EntitySyntaxId& entityId)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entityId, *this);
		const auto& identifier = entityId->identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			Log::error("Name `$` is already declared in global scope.", identifier);

		return result;
	}

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

	Optional<EntitySyntaxId> GlobalSymbolTable::resolve(const Identifier&) const
	{
		Log::notImplemented(here());
	}

	Optional<EntitySyntaxId> GlobalSymbolTable::resolve(const QualifiedIdentifier&) const
	{
		Log::notImplemented(here());
	}
}
