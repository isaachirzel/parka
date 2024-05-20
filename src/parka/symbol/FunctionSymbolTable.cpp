#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/symbol/ParameterEntry.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/validator/Validator.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(SymbolTable& parent):
		LocalSymbolTable(SymbolTableType::Function),
		_global(parent.globalSymbolTable()),
		_parent(parent),
		_scope(),
		_symbols(),
		_variables(),
		_parameters(),
		_returnType(ir::TypeIr::voidType),
		_isExplicitReturnType(false),
		_parentStatements()
	{}

	VariableEntry& FunctionSymbolTable::addVariable(VariableEntry&& entry)
	{
		return _variables.push(std::move(entry));
	}

	ParameterEntry& FunctionSymbolTable::addParameter(ParameterEntry&& entry)
	{
		return _parameters.push(std::move(entry));
	}

	FunctionEntry& FunctionSymbolTable::declare(const ast::FunctionAst&)
	{
		throw std::invalid_argument("Functions cannot be declared in a FunctionSymbolTable.");
	}

	ParameterEntry& FunctionSymbolTable::declare(const ast::ParameterAst& ast)
	{
		auto* ir = validator::validateParameter(ast, *this);
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

	VariableEntry& FunctionSymbolTable::declare(const ast::VariableAst& ast)
	{
		auto* ir = validator::validateVariable(ast, *this);
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

	Resolvable* FunctionSymbolTable::findSymbol(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		auto** symbol = _symbols.find(name);

		if (!symbol)
			return {};

		return *symbol;
	}

	ir::LValueIr* FunctionSymbolTable::resolveSymbol(const ast::QualifiedIdentifier& identifier)
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

	ir::BinaryOperatorIr* FunctionSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right)
	{
		return _global.resolveBinaryOperator(binaryExpressionType, left, right);
	}

	Result<ir::ConversionIr*> FunctionSymbolTable::resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from)
	{
		return _global.resolveConversion(to, from);
	}
}
