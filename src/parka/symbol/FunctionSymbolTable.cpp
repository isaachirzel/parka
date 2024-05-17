#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/log/Indent.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(SymbolTable& parent):
		SymbolTable(SymbolTableType::Function),
		_global(parent.global()),
		_parent(parent),
		_scope(),
		_symbols(),
		_variables(),
		_parameters(),
		_returnType(ir::Type::voidType),
		_parentStatements()
	{}

	bool FunctionSymbolTable::declare(const ast::Identifier& identifier, Resolvable *resolvable)
	{
		auto *previous = findSymbol(identifier);

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

	ParameterEntry* FunctionSymbolTable::declare(ParameterEntry&& entry)
	{
		auto& ref = _parameters.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);
		
		if (!success)
			return nullptr;

		return ptr;
	}

	VariableEntry* FunctionSymbolTable::declare(VariableEntry&& entry)
	{
		auto& ref = _variables.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);

		if (!success)
			return nullptr;

		return ptr;
	}

	Resolvable* FunctionSymbolTable::findSymbol(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		// TODO: Iterate in reverse
		for (auto *entity : _symbols)
		{
			auto* a = (void*)entity;
			if (entity->name() == name)
				return entity;
		}

		return nullptr;
	}

	ir::LValueIr* FunctionSymbolTable::resolveSymbol(const ast::QualifiedIdentifier& identifier)
	{
		if (identifier.isAbsolute())
			return _global.resolveSymbol(identifier);

		if (identifier.length() > 1)
			return _parent.resolveSymbol(identifier);

		auto *local = findSymbol(identifier[0]);

		if (local)
			return local->resolve();

		auto *global = _parent.resolveSymbol(identifier);
 
		return global;
	}

	ir::BinaryOperatorIr* FunctionSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::Type& left, const ir::Type& right)
	{
		return _global.resolveBinaryOperator(binaryExpressionType, left, right);
	}

	Result<ir::ConversionIr*> FunctionSymbolTable::resolveConversion(const ir::Type& to, const ir::Type& from)
	{
		return _global.resolveConversion(to, from);
	}
	
	std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& symbolTable)
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
