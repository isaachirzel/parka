#ifndef PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/enum/SymbolTableEntryType.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include <cassert>

namespace parka
{
	class SymbolTableEntry
	{
		EntitySyntaxId _syntaxId;
		Optional<EntityContextId> _contextId;
		
		union
		{
			PackageSymbolTable _package;
			StructSymbolTable _struct;
		};

	public:

		SymbolTableEntry(const EntitySyntaxId& entityId, const SymbolTable& parent);
		SymbolTableEntry(SymbolTableEntry&&);
		SymbolTableEntry(const SymbolTableEntry&) = delete;
		~SymbolTableEntry();

		void setParent(const SymbolTable& parent);

		const auto& syntaxId() const {  return _syntaxId; }
		const auto& contextId() const {  return _contextId; }
		const auto& type() const { return _syntaxId.type(); }

		auto& contextId() {  return _contextId; }
		auto& packageSymbolTable() { assert(_syntaxId.type() == EntityType::Package); return _package; }
		auto& structSymbolTable() { assert(_syntaxId.type() == EntityType::Struct); return _struct; }

		friend std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry);
	};
}

#endif
