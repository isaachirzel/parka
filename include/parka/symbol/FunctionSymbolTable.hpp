#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"

// TODO: Move constructor

namespace parka
{
	class FunctionSymbolTable : public SymbolTable
	{
		EntitySyntaxId _syntaxId;
		const SymbolTable *_parent;
		Array<EntitySyntaxId> _symbols;
		Array<usize> _blockIndexes;

	public:

		FunctionSymbolTable(const EntitySyntaxId& syntaxId, const SymbolTable& parent);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const EntitySyntaxId& entityId);

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntaxId& blockId);
		void popBlock();
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		const SymbolTable *getParent() const { return _parent; }

		const auto& syntaxId() const { return _syntaxId; }
	};
}

#endif

