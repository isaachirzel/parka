#ifndef PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYBMOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/EntitySyntax.hpp"

#include <cassert>

namespace parka
{
	class SymbolTableEntry
	{
		const EntitySyntax& _syntax;
		const EntityContext *_context;
	
	public:

		SymbolTableEntry(const EntitySyntax& entity, SymbolTable& parent);
		SymbolTableEntry(SymbolTableEntry&&) = default;
		SymbolTableEntry(const SymbolTableEntry&) = delete;

		void setParent(SymbolTable& parent);
		void setContext(const EntityContext& context);

		const auto& syntax() const {  return _syntax; }
		const auto& context() const {  return _context; }

		friend std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry);
	};
}

#endif
