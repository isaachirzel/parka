#ifndef PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/enum/SymbolTableEntryType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include <cassert>

namespace parka
{
	class SymbolTableEntry
	{
		const EntitySyntax& _syntax;
		const EntityContext *_context;
		
		union
		{
			PackageSymbolTable _package;
			StructSymbolTable _struct;
		};

	public:

		SymbolTableEntry(const EntitySyntax& entity, const SymbolTable& parent);
		SymbolTableEntry(SymbolTableEntry&&);
		SymbolTableEntry(const SymbolTableEntry&) = delete;
		~SymbolTableEntry();

		void setParent(const SymbolTable& parent);

		const auto& syntax() const {  return _syntax; }
		const auto& context() const {  return _context; }

		auto& context() {  return _context; }
		auto& packageSymbolTable() { assert(_syntax.type() == EntityType::Package); return _package; }
		auto& structSymbolTable() { assert(_syntax.type() == EntityType::Struct); return _struct; }

		friend std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry);
	};
}

#endif
