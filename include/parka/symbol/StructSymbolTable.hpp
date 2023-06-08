#ifndef PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP

#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/util/Table.hpp"

// TODO: Figure out what to do here. Perhaps add member to entity list
namespace parka
{
	class StructSymbolTable : public SymbolTable
	{
		const StructSyntax& _syntax;
		const SymbolTable *_parent;
		Table<String, const EntitySyntax*> _symbols;

		StructSymbolTable(const StructSyntax& syntax, const SymbolTable& parent);

	public:

		EntitySyntax *resolve(const Identifier& identifier) const;
		EntitySyntax *resolve(const QualifiedIdentifier& identifier) const;
		
		const SymbolTable *getParent() const { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Struct; }

		friend class SymbolTableEntry;
	};
}

#endif
