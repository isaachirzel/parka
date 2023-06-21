#include "parka/ast/Parameter.hpp"
#include "parka/ir/Parameter.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"

#include "parka/util/Print.hpp"

namespace parka::ast
{
	// ir::ParameterIr *ParameterAst::validate(SymbolTable& symbolTable)
	// {
	// 	auto isDeclared = _parent->declare(*this);
	// 	auto valueType = _annotation.validate(symbolTable);

	// 	if (!isDeclared || !valueType)
	// 		return nullptr;

	// 	auto *context = new ir::ParameterIr(*valueType);

	// 	return context;
	// }

	String ParameterAst::getSymbol() const
	{
		return name();
	}

	std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax)
	{
		if (syntax._isMutable)
			out << "mut ";

		out << syntax._identifier;
		// TODO: Add annotation

		return out;
	}
}
