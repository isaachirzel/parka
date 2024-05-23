#include "parka/log/Log.hpp"
#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/validator/Validator.hpp"

namespace parka
{
	BlockSymbolTable::BlockSymbolTable(LocalSymbolTable& parent):
		LocalSymbolTable(SymbolTableType::Block),
		_global(parent.globalSymbolTable()),
		_function(parent.functionSymbolTable()),
		_parent(parent),
		_scope(),
		_symbols(),
		_isInLoop(false)
	{}

	FunctionEntry& BlockSymbolTable::declare(const ast::FunctionAst&)
	{
		throw std::invalid_argument("Functions cannot be declared in a BlockSymbolTable.");
	}

	ParameterEntry& BlockSymbolTable::declare(const ast::ParameterAst&)
	{
		throw std::invalid_argument("Parameters cannot be declared in a BlockSymbolTable.");
	}

	VariableEntry& BlockSymbolTable::declare(const ast::VariableAst& ast)
	{
		auto* ir = validator::validateVariable(ast, *this);
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

	Resolvable* BlockSymbolTable::findSymbol(const ast::IdentifierAst& identifier)
	{
		const auto& name = identifier.text();
		auto** symbol = _symbols.find(name);

		if (!symbol)
			return {};

		return *symbol;
	}

	ir::LValueIr* BlockSymbolTable::resolveSymbol(const ast::QualifiedIdentifierAst& identifier)
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

	ir::BinaryOperatorIr* BlockSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right)
	{
		return _global.resolveBinaryOperator(binaryExpressionType, left, right);
	}

	Result<ir::ConversionIr*> BlockSymbolTable::resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from)
	{
		return _global.resolveConversion(to, from);
	}
}
