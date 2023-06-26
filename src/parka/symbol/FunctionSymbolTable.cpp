#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::validator
{


	FunctionSymbolTable::FunctionSymbolTable(const ast::FunctionAst& ast, SymbolTable *parent):
	SymbolTable(SymbolTableType::Function),
	Resolvable(ResolvableType::Function),
	_ast(ast),
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

				const auto *previous = dynamic_cast<const Declarable*>(symbol);

				if (previous != nullptr)
					log::note(previous->identifier(), "Previous declaration here:");
					
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		switch (declarable.declarableType)
		{
			case DeclarableType::Variable:
			{
				auto *ast = static_cast<const ast::VariableAst*>(&declarable);
				auto& resolvable = _variables.push(VariableEntry(*ast, *this));

				_symbols.push(&resolvable);

				return true;
			}

			case DeclarableType::Parameter:
			{
				auto *ast = static_cast<const ast::ParameterAst*>(&declarable);
				auto& resolvable = _parameters.push(ParameterEntry(*ast, *this));

				_symbols.push(&resolvable);

				return true;
			}

			default:
				break;
		}

		// TODO: Implement declarable type printing
		log::fatal("Unable to declare Declarable with Type: $", (int)declarable.declarableType);
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
