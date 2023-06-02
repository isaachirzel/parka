#ifndef PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/enum/SymbolTableEntryType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include <cassert>

namespace parka
{
	class SymbolTableEntry
	{
		EntitySyntaxId _entityId;
		
		union
		{
			PackageSymbolTable _package;
			FunctionSymbolTable _function;
		};

		EntityType _type;

	public:

		SymbolTableEntry(const EntitySyntaxId& entityId, const SymbolTable& parent);
		SymbolTableEntry(SymbolTableEntry&&);
		SymbolTableEntry(const SymbolTableEntry&) = delete;
		~SymbolTableEntry();

		void setParent(const SymbolTable& parent);

		// TODO: Safety asserts
		const auto& entityId() const {  return _entityId; }
		const auto& package() const { return _package; }
		const auto& function() const { return _function; }
		const auto& type() const { return _type; }
	};
}

#endif
