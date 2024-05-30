#include "parka/validation/FunctionContext.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/GlobalContext.hpp"
#include "parka/validation/ParameterEntry.hpp"
#include "parka/validation/ContextEntry.hpp"
#include "parka/validation/VariableEntry.hpp"
#include "parka/validation/Validator.hpp"

namespace parka::validation
{
	FunctionContext::FunctionContext(Context& parent):
		LocalContext(ContextType::Function),
		_global(parent.globalContext()),
		_parent(parent),
		_scope(),
		_symbols(),
		_variables(),
		_parameters(),
		_returnType(&ir::PrimitiveIr::voidPrimitive),
		_isExplicitReturnType(false)
	{}

	VariableEntry& FunctionContext::addVariable(VariableEntry&& entry)
	{
		return _variables.push(std::move(entry));
	}

	ParameterEntry& FunctionContext::addParameter(ParameterEntry&& entry)
	{
		return _parameters.push(std::move(entry));
	}

	FunctionEntry& FunctionContext::declare(const ast::FunctionAst&)
	{
		throw std::invalid_argument("Functions cannot be declared in a FunctionContext.");
	}

	ParameterEntry& FunctionContext::declare(const ast::ParameterAst& ast)
	{
		auto* ir = validation::validateParameter(ast, *this);
		auto& ref = addParameter(ParameterEntry(ast, ir));
		auto insertion = _symbols.insert(ast.identifier().text(), &ref);

		if (!insertion)
		{
			auto* previous = *insertion;
			log::error(ast.identifier(), "This parameter list already has a $ with the name `$`.", previous->resolvableType, previous->name());

			// TODO: Previously declared here error
		}

		return ref;
	}

	VariableEntry& FunctionContext::declare(const ast::VariableAst& ast)
	{
		auto* ir = validation::validateVariable(ast, *this);
		auto& ref = addVariable(VariableEntry(ast, ir));
		auto insertion = _symbols.insert(ast.identifier().text(), &ref);

		if (!insertion)
		{
			auto* previous = *insertion;
			log::error(ast.identifier(), "Declaration of variable `$` shadows a $ with the same name.", previous->name(), previous->resolvableType);

			// TODO: Previously declared here error
		}

		return ref;
	}

	ContextEntry* FunctionContext::findSymbol(const ast::IdentifierAst& identifier)
	{
		const auto& name = identifier.text();
		auto** symbol = _symbols.find(name);

		if (!symbol)
			return {};

		return *symbol;
	}

	ir::EntityIr* FunctionContext::resolveSymbol(const ast::QualifiedIdentifierAst& identifier)
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
