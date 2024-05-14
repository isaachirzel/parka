#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/IdentifierAst.hpp"

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
