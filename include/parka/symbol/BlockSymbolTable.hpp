#ifndef PARKA_SYMBOL_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_BLOCK_SYMBOL_TABLE_HPP

#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"

namespace parka
{
	class BlockSymbolTable : public SymbolTable
	{
		FunctionSymbolTable& _parent;
		Array<const EntitySyntax*>& _symbols;
		usize _baseIndex;

	private:

		bool declare(const EntitySyntax& entity);

	public:

		BlockSymbolTable(FunctionSymbolTable& symbolTable);
		BlockSymbolTable(BlockSymbolTable&&) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;
		~BlockSymbolTable();

		const EntityContext *resolve(const Identifier& identifier);
		const EntityContext *resolve(const QualifiedIdentifier& identifier);
		SymbolTableType symbolTableType() const { return SymbolTableType::Block; }
		SymbolTable *parent() { return &_parent; }
	};
}

#endif
