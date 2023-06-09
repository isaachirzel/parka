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
		SymbolTable *_parent;
		const StructSyntax& _syntax;
		Table<String, const EntitySyntax*> _symbols;

		StructSymbolTable(const StructSyntax& syntax, SymbolTable& parent);

	public:

		const EntityContext *resolve(const Identifier& identifier);
		const EntityContext *resolve(const QualifiedIdentifier& identifier);
		
		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Struct; }

		friend class SymbolTableEntry;
	};
}

#endif
