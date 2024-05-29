#include "parka/log/Log.hpp"
#include "parka/validation/BlockContext.hpp"
#include "parka/validation/GlobalContext.hpp"
#include "parka/validation/LocalContext.hpp"
#include "parka/validation/Context.hpp"
#include "parka/validation/Validator.hpp"

namespace parka::validation
{
	BlockContext::BlockContext(LocalContext& parent):
		LocalContext(ContextType::Block),
		_global(parent.globalContext()),
		_function(parent.functionContext()),
		_parent(parent),
		_scope(),
		_symbols(),
		_isInLoop(false)
	{}

	FunctionEntry& BlockContext::declare(const ast::FunctionAst&)
	{
		throw std::invalid_argument("Functions cannot be declared in a BlockContext.");
	}

	ParameterEntry& BlockContext::declare(const ast::ParameterAst&)
	{
		throw std::invalid_argument("Parameters cannot be declared in a BlockContext.");
	}

	VariableEntry& BlockContext::declare(const ast::VariableAst& ast)
	{
		auto* ir = validation::validateVariable(ast, *this);
		auto& ref = _function.addVariable(VariableEntry(ast, ir));
		auto insertion = _symbols.insert(ast.identifier().text(), &ref);

		if (!insertion)
		{
			auto* previous = *insertion;
			log::error(ast.identifier(), "Declaration of variable `$` shadows a $ with the same name.", previous->name(), previous->resolvableType);

			// TODO: Previously declared here error
		}

		return ref;
	}

	Resolvable* BlockContext::findSymbol(const ast::IdentifierAst& identifier)
	{
		const auto& name = identifier.text();
		auto** symbol = _symbols.find(name);

		if (!symbol)
			return {};

		return *symbol;
	}

	ir::EntityIr* BlockContext::resolveSymbol(const ast::QualifiedIdentifierAst& identifier)
	{
		if (identifier.isAbsolute())
			return _global.resolveSymbol(identifier);

		if (identifier.length() > 1)
			return _parent.resolveSymbol(identifier);

		auto *symbol = findSymbol(identifier[0]);

		if (symbol)
			return symbol->resolve();

		return _parent.resolveSymbol(identifier);
	}
}
