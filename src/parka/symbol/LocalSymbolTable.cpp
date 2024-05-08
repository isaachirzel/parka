#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ir/LValue.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/log/Indent.hpp"

namespace parka
{
	LocalSymbolTable::LocalSymbolTable(SymbolTable *parent):
		SymbolTable(SymbolTableType::Function),
		_parent(parent)
	{}

	bool LocalSymbolTable::declare(const ast::Identifier& identifier, Resolvable *resolvable)
	{
		auto *previous = find(identifier);

		if (previous)
		{
			// TODO: maybe just insert it anyways?
			log::error(identifier, "A $ `$` has already been declared in this function.", previous->resolvableType, identifier.text());
			return false;
		}

		_symbols.push(resolvable);
		// TODO: show previous declaration
		
		return true;
	}

	ParameterEntry *LocalSymbolTable::declare(ParameterEntry&& entry)
	{
		auto& ref = _parameters.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);
		
		if (!success)
			return nullptr;

		return ptr;
	}

	VariableEntry *LocalSymbolTable::declare(VariableEntry&& entry)
	{
		auto& ref = _variables.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);

		if (!success)
			return nullptr;

		return ptr;
	}

	Resolvable *LocalSymbolTable::find(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		// TODO: Iterate in reverse
		for (auto *entity : _symbols)
		{
			if (entity->name() == name)
				return entity;
		}

		return nullptr;
	}

	ir::LValue *LocalSymbolTable::resolve(const ast::QualifiedIdentifier& identifier)
	{
		assert(_parent != nullptr);

		if (identifier.isAbsolute() || identifier.length() > 1)
			return _parent->resolve(identifier);

		auto *local = find(identifier[0]);

		if (local)
			return local->resolve();

		auto *global = _parent->resolve(identifier);
 
		return global;
	}

	ir::OperatorIr *LocalSymbolTable::resolve(OperatorType type, const ir::Type& left, const ir::Type *right)
	{
		assert(_parent != nullptr);

		return _parent->resolve(type, left, right);
	}

	ir::ConversionIr *LocalSymbolTable::resolveConversion(const ir::Type& from, const ir::Type& to)
	{
		assert(_parent != nullptr);

		return _parent->resolveConversion(from, to);
	}
	
	std::ostream& operator<<(std::ostream& out, const LocalSymbolTable& symbolTable)
	{
		// out << validator._ast.prototype();
		out << symbolTable._scope << '\n';

		auto indent = Indent(out);

		for (const auto *symbol : symbolTable._symbols)
		{
			out << indent << symbol->name() << '\n';
		}

		return out;
	}
}
