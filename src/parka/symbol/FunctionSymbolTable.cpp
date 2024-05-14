#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/log/Indent.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(SymbolTable *parent):
		SymbolTable(SymbolTableType::Function),
		_scope(),
		_symbols(),
		_variables(),
		_parameters(),
		_returnType(ir::Type::voidType),
		_parent(parent)
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

	ParameterEntry *FunctionSymbolTable::declare(ParameterEntry&& entry)
	{
		auto& ref = _parameters.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);
		
		if (!success)
			return nullptr;

		return ptr;
	}

	VariableEntry *FunctionSymbolTable::declare(VariableEntry&& entry)
	{
		auto& ref = _variables.push(std::move(entry));
		auto *ptr = &ref;
		auto success = declare(entry.identifier(), ptr);

		if (!success)
			return nullptr;

		return ptr;
	}

	Resolvable *FunctionSymbolTable::findSymbol(const ast::Identifier& identifier)
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

	ir::LValueIr *FunctionSymbolTable::resolveSymbol(const ast::QualifiedIdentifier& identifier)
	{
		assert(_parent != nullptr);

		if (identifier.isAbsolute() || identifier.length() > 1)
			return _parent->resolveSymbol(identifier);

		auto *local = findSymbol(identifier[0]);

		if (local)
			return local->resolve();

		auto *global = _parent->resolveSymbol(identifier);
 
		return global;
	}

	ir::BinaryOperatorIr *FunctionSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::Type& left, const ir::Type& right)
	{
		assert(_parent != nullptr);

		return _parent->resolveBinaryOperator(binaryExpressionType, left, right);
	}

	ir::ConversionIr *FunctionSymbolTable::resolveConversion(const ir::Type& from, const ir::Type& to)
	{
		assert(_parent != nullptr);

		return _parent->resolveConversion(from, to);
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
