#ifndef PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP
#define PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/symbol/ParameterEntry.hpp"

namespace parka
{
	class LocalSymbolTable: public SymbolTable
	{
		String _scope;
		Array<Resolvable*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		SymbolTable *_parent;

	private:

		bool declare(const ast::Identifier& identifier, Resolvable *resolvable);

	public:

		LocalSymbolTable(SymbolTable *parent = nullptr):
		SymbolTable(SymbolTableType::Function),
		_parent(parent)
		{}
		LocalSymbolTable(LocalSymbolTable&&) = default;
		LocalSymbolTable(const LocalSymbolTable&) = delete;

		ParameterEntry *declare(ParameterEntry&& entry);
		VariableEntry *declare(VariableEntry&& entry);
		Resolvable *find(const ast::Identifier& identifier);
		Resolution *resolve(const ast::QualifiedIdentifier& identifier);

		const String& scope() const { return _scope; }

		friend std::ostream& operator<<(std::ostream& out, const LocalSymbolTable& syntax);
	};
}

#endif
