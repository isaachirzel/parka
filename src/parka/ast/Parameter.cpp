#include "parka/ast/ParameterAst.hpp"
#include "parka/ir/ParameterIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"

#include "parka/util/Print.hpp"

namespace parka::ast
{
	std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax)
	{
		if (syntax._isMutable)
			out << "mut ";

		out << syntax._identifier;
		// TODO: Add annotation

		return out;
	}
}
