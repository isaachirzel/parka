#ifndef PARKA_SYMBOL_PACKAGE_ENTRY_HPP
#define PARKA_SYMBOL_PACKAGE_ENTRY_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/PackageIr.hpp"

namespace parka
{
	class PackageEntry: public Resolvable
	{
		const ast::PackageAst& _ast;
		ir::PackageIr * _ir;
		bool _isValidated;
		// TODO: resolve mutex

	public:

		PackageEntry(const ast::PackageAst& ast):
		Resolvable(ResolvableType::Package),
		_ast(ast),
		_ir(nullptr),
		_isValidated(false)
		{}

		ir::PackageIr *resolve();

		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.name(); }
	};
}

#endif
