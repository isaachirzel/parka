#include "parka/ast/Prototype.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/Type.hpp"
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
