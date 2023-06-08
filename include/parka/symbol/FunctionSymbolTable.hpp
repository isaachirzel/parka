#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

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
		const FunctionSyntax& _syntax;
		const SymbolTable *_parent;
		Array<const EntitySyntax*> _symbols;
		Array<usize> _blockIndexes;

	public:

		FunctionSymbolTable(const FunctionSyntax& syntax, const SymbolTable& parent);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const EntitySyntax& entityId);

		const EntitySyntax *resolve(const Identifier& identifier) const;
		const EntitySyntax *resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntax& blockId);
		void popBlock();
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		const SymbolTable *getParent() const { return _parent; }

		const auto& syntax() const { return (const FunctionSyntax&)_syntax; }
	};
}

#endif

