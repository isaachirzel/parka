#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::validator
{
	FunctionSymbolTable::FunctionSymbolTable(ast::FunctionAst& ast, SymbolTable *parent):
	SymbolTable(SymbolTableType::Function),
	Resolvable(ResolvableType::Function),
	_ast(ast),
	_scope(),
	_symbols(),
	_parent(parent),
	_ir(nullptr)
	{}

	bool FunctionSymbolTable::declare(const Declarable& declarable)
	{
		const auto& identifier = declarable.identifier();
		const auto& name = identifier.text();

		for (auto *symbol : _symbols)
		{
			if (name == symbol->name())
			{
				log::error(identifier, "A $ `$` has already been declared in this function.", declarable.declarableType, name);

				auto *previous = dynamic_cast<Declarable*>(symbol);

				if (previous != nullptr)
					log::note(previous->identifier(), "Previous declaration here:");
					
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		// TODO: Do not do this this way
		auto *resolvable = dynamic_cast<Resolvable*>(&declarable);

		assert(resolvable != nullptr);

		_symbols.push(resolvable);
		
		return true;
	}

	Resolvable *FunctionSymbolTable::find(const ast::Identifier& identifier)
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

	Resolution *FunctionSymbolTable::resolve(const ast::QualifiedIdentifier&)
	{
		log::notImplemented(here());
		// if (identifier.isAbsolute() || identifier.length() > 1)
		// 	return _parent->resolve(identifier);

		// auto *local = find(identifier[0]);

		// if (local != nullptr)
		// 	return local->context();

		// auto *global = _parent->resolve(identifier);
 
		// return global;
	}
	
	std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& validator)
	{
		out << validator._ast.prototype();

		return out;
	}
}
