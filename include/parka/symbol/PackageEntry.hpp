#ifndef PARKA_SYMBOL_PACKAGE_ENTRY_HPP
#define PARKA_SYMBOL_PACKAGE_ENTRY_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/PackageIr.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class PackageEntry: public Resolvable
	{
		const ast::PackageAst& _ast;
		PackageSymbolTable _symbolTable;
		ir::PackageIr * _ir;
		bool _isValidated;

	public:

		PackageEntry(const ast::PackageAst& ast, SymbolTable& parent):
			Resolvable(ResolvableType::Package),
			_ast(ast),
			_symbolTable(ast, parent),
			_ir(nullptr),
			_isValidated(false)
		{}

		ir::PackageIr *resolve();

		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.name(); }
	};
}

#endif
