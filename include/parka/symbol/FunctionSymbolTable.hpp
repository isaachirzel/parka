#ifndef PARKA_SYMBOL_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/symbol/ParameterEntry.hpp"

namespace parka
{
	class FunctionSymbolTable: public SymbolTable
	{
		String _scope;
		Array<Resolvable*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		Result<ir::Type> _returnType;
		SymbolTable *_parent;

	private:

		bool declare(const ast::Identifier& identifier, Resolvable *resolvable);

	public:

		FunctionSymbolTable(SymbolTable *parent = nullptr);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		ParameterEntry *declare(ParameterEntry&& entry);
		VariableEntry *declare(VariableEntry&& entry);
		Resolvable *find(const ast::Identifier& identifier);
		ir::LValueIr *resolve(const ast::QualifiedIdentifier& identifier);
		ir::OperatorIr *resolve(OperatorType type, const ir::Type& left, const ir::Type *right);
		ir::ConversionIr *resolveConversion(const ir::Type& from, const ir::Type& to);

		void setReturnType(const ir::Type& type) { _returnType = type; }
		const auto& returnType() const { return *_returnType; }
		const String& scope() const { return _scope; }

		friend std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& syntax);
	};
}

#endif
