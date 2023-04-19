#ifndef PARKA_CONTEXT_HPP
#define PARKA_CONTEXT_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class DeclarationStatementSyntax;
	class ExpressionStatementSyntax;
	class JumpStatementSyntax;

	struct SyntaxRepositor
	{
		// static PackageSyntax& getPackage(const EntitySyntaxId& id);
		// static StructSyntax& getStruct(const EntitySyntaxId& id);
		// static FunctionSyntax& getFunction(const EntitySyntaxId& id);
		// static VariableSyntax& getVariable(const EntitySyntaxId& id);
		// static ParameterSyntax& getParameter(const EntitySyntaxId& id);

		// static EntitySyntaxId getId(FunctionSyntax& value);
		// static EntitySyntaxId getId(PackageSyntax& value);
	};
}

#endif
