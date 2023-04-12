#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class FunctionSymbolTable : public SymbolTable
	{
		EntitySyntaxId _functionId;
		const SymbolTable& _parent;
		Table<String, EntitySyntaxId> _symbols;
		Array<BlockSymbolTable> _blocks;

		FunctionSymbolTable(const EntitySyntaxId& functionId, const SymbolTable& parent) :
		_functionId(functionId),
		_parent(parent)
		{}

	public:

		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;
		~FunctionSymbolTable() = default;

		static Optional<FunctionSymbolTable> from(const FunctionSyntax& function);

		bool declare(const Identifier& identifier);
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntaxId& blockId);
	};
}

#endif

