#include "parka/validation/PackageContext.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include <stdexcept>

namespace parka::validation
{
	PackageContext::PackageContext(const ast::PackageAst& ast, Context& parent):
		Context(ContextType::Package),
		_scope(parent.createSymbol(ast.name())),
		_symbols(),
		_global(parent.globalContext()),
		_parent(parent)
	{
		log::notImplemented(here());
	}

	FunctionEntry& PackageContext::declare(const ast::FunctionAst& ast)
	{
		auto& entry = _global.addFunction(FunctionEntry(ast, *this));
		const auto& key = ast.prototype().identifier().text();
		auto insertion = _symbols.insert(key, &entry);

		if (!insertion)
		{
			auto* previous = *insertion;

			log::error(ast.prototype().identifier(), "A $ with the name `$` has already been declared in the package $.", previous->resolvableType, previous->name(), _scope);
		}

		return entry;
	}

	VariableEntry& PackageContext::declare(const ast::VariableAst&)
	{
		throw std::invalid_argument("Variables cannot be declared in a PackageContext.");
	}

	ParameterEntry& PackageContext::declare(const ast::ParameterAst&)
	{
		throw std::invalid_argument("Parameters cannot be declared in a PackageContext.");

	}

	Resolvable* PackageContext::findInitialSymbol(const ast::IdentifierAst& identifier)
	{
		const auto& name = identifier.text();
		auto *package = (Context*)this;

		do
		{
			auto *entry = package->findSymbol(identifier);

			if (entry != nullptr)
				return entry;

			if (entry->name() == name)
				return entry;

			package = package->parent();
		}
		while (package != nullptr);

		return nullptr;
	}

	Resolvable* PackageContext::findSymbol(const ast::IdentifierAst& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	ir::EntityIr* PackageContext::resolveSymbol(const ast::QualifiedIdentifierAst& qualifiedIdentifier)
	{
		if (qualifiedIdentifier.isAbsolute())
			return _global.resolveSymbol(qualifiedIdentifier);

		const auto& first = qualifiedIdentifier[0];
		auto *entry = findInitialSymbol(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			// TODO: Figure out how to not use dynamic cast in this

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = entry->context();

			if (table == nullptr)
			{
				log::error(identifier.snippet(), "Unable to resolve `$` in package `$`.", identifier, entry->name());
				return nullptr;
			}

			entry = table->findSymbol(identifier);
		}

		if (entry != nullptr)
			return entry->resolve();

		return nullptr;
	}
}
