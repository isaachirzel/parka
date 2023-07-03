#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/validator/Validator.hpp"
#include "parka/log/Indent.hpp"

namespace parka
{
	bool LocalSymbolTable::hasPrevious(const ast::Identifier& identifier)
	{
		auto *previous = find(identifier);

		if (!previous)
			return false;

		log::error(identifier, "A $ `$` has already been declared in this function.", previous->resolvableType, identifier.text());

		// TODO: show previous declaration			
		// TODO: maybe just insert it anyways?
		
		return true;
	}

	ParameterEntry *LocalSymbolTable::declare(ParameterEntry&& entry)
	{
		if (hasPrevious(entry.identifier()))
			return nullptr;

		auto& ref = _parameters.push(std::move(entry));

		return &ref;
	}

	VariableEntry *LocalSymbolTable::declare(VariableEntry&& entry)
	{
		if (hasPrevious(entry.identifier()))
			return nullptr;

		auto& ref = _variables.push(std::move(entry));

		return &ref;
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

	Resolution *LocalSymbolTable::resolve(const ast::QualifiedIdentifier& identifier)
	{
		// log::notImplemented(here());
		if (identifier.isAbsolute() || identifier.length() > 1)
			return _parent->resolve(identifier);

		auto *local = find(identifier[0]);

		if (local)
			return local->resolve();

		auto *global = _parent->resolve(identifier);
 
		return global;
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
