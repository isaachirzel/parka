#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	ParameterAst::ParameterAst(const fs::FileSnippet& snippet, IdentifierAst&& identifier, TypeAnnotationAst&& annotation, bool isMutable):
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isMutable(isMutable)
	{}

	std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax)
	{
		if (syntax._isMutable)
			out << "mut ";

		out << syntax._identifier;
		// TODO: Add annotation

		return out;
	}
}
