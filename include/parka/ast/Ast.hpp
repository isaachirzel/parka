#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ir/Entity.hpp"
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
		_globalPackage(globalPackage)
		{}
		Ast(Ast&&) = default;
		Ast(const Ast&) = delete;

		static Ast parse(const Project& project);

		bool declare(EntityAst& syntax);
		bool declareSelf();
		SymbolTableEntry *find(const Identifier& identifier);
		ir::EntityIr *resolve(const QualifiedIdentifier& identifier);

		Optional<ir::Ir> validate();

		SymbolTableType symbolTableType() const { return SymbolTableType::Global; }

		friend std::ostream& operator<<(std::ostream& out, const Ast& syntax);
	};
}

#endif
