#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/ast/ModuleAst.hpp"

namespace parka::ast
{
	class PackageAst
	{
		String _name;
		Array<ModuleAst> _modules;
		Array<PackageAst*> _packages;

	public:

		PackageAst(String&& identifier, Array<ModuleAst>&& modules, Array<PackageAst*>&& packages):
			_name(std::move(identifier)),
			_modules(std::move(modules)),
			_packages(std::move(packages))
		{}
		PackageAst(PackageAst&&) = default;
		PackageAst(const PackageAst&) = delete;
		
		const String& name() const { return _name; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }
	};
}

#endif
