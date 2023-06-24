#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Package.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class Ast
	{
		PackageAst& _globalPackage;
		// TODO: Project metadata
		// TODO: External package ids
		
	public:

		Ast(PackageAst& globalPackage):
		_globalPackage(globalPackage)
		{}
		Ast(Ast&&) = default;
		Ast(const Ast&) = delete;

		const auto& globalPackage() const { return _globalPackage; }

		friend std::ostream& operator<<(std::ostream& out, const Ast& syntax);
	};
}

#endif
