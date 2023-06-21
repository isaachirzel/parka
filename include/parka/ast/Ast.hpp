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
	class Ast : public SymbolTable
	{
		// TODO: Project metadata
		PackageAst& _globalPackage;
		// TODO: External package ids
		
	public:

		Ast(PackageAst& globalPackage) :
		SymbolTable(SymbolTableType::Global),
		_globalPackage(globalPackage)
		{}
		Ast(Ast&&) = default;
		Ast(const Ast&) = delete;

		bool declare(Declarable& declarable);
		bool declareSelf();
		Resolvable *find(const Identifier& identifier);
		Resolution *resolve(const QualifiedIdentifier& identifier);

		friend std::ostream& operator<<(std::ostream& out, const Ast& syntax);
	};
}

#endif
