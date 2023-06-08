#include "parka/context/ContextTree.hpp"
#include "parka/context/PackageContext.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/intrinsic/Primitive.hpp"

namespace parka
{
	Optional<ContextTree> ContextTree::validate(const SyntaxTree& syntax)
	{
		auto symbolTable = PackageSymbolTable(syntax.globalPackage(), nullptr);

		std::cout << symbolTable << std::endl;

		const auto *globalPackage = PackageContext::validate(symbolTable);

		if (!globalPackage)
			return {};

		auto context = ContextTree(*globalPackage);

		return context;
	}
}

/*
things must be validated before they can be accessed
a function needs to be made to get the EntityContextId for a given QualifiedIdentifier
this function will access the symbol table, find the SymbolTableEntry, try to slock the mutex,
and upon getting the lock, it will check if it vali
*/
