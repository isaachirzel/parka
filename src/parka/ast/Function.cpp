#include "parka/ast/Function.hpp"
#include "parka/ir/Function.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/Package.hpp"

namespace parka::ast
{
	bool FunctionAst::declareSelf(PackageAst&)//parent)
	{
		log::notImplemented(here());
		// _parent = &parent;

		// return parent.declare(*this);
	}

	bool FunctionAst::declare(Declarable& declarable)
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

		_symbols.push(&declarable);
		
		return true;
	}

	Resolvable *FunctionAst::find(const Identifier& identifier)
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

	Resolution *FunctionAst::resolve(const QualifiedIdentifier&)
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

	String FunctionAst::getSymbol() const
	{
		assert(_parent != nullptr);

		auto symbol = _parent->getSymbol();

		symbol += "::";
		symbol += name();

		return symbol;
	}

	std::ostream& operator<<(std::ostream& out, const FunctionAst& syntax)
	{
		out << syntax._prototype;

		return out;
	}
}
