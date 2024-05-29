#ifndef PARKA_VALIDATION_PACKAGE_ENTRY_HPP
#define PARKA_VALIDATION_PACKAGE_ENTRY_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/PackageIr.hpp"
#include "parka/validation/PackageContext.hpp"
#include "parka/validation/ContextEntry.hpp"

namespace parka::validation
{
	class PackageEntry: public ContextEntry
	{
		const ast::PackageAst& _ast;
		PackageContext _symbolTable;
		ir::PackageIr * _ir;
		bool _isValidated;

	public:

		PackageEntry(const ast::PackageAst& ast, Context& parent):
			ContextEntry(ResolvableType::Package),
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
