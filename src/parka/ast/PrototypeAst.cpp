#include "parka/ast/PrototypeAst.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	std::ostream& operator<<(std::ostream& out, const PrototypeAst& ast)
	{
		out << "function " << ast._identifier << '(';

		bool isFirst = true;

		for (const auto *parameter : ast._parameters)
		{
			if (!isFirst)
				out << ", ";

			out << *parameter;

			isFirst = false;
		}

		out << ")";

		return out;
	}
}
