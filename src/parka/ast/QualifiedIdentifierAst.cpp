#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	std::ostream& operator<<(std::ostream& out, const QualifiedIdentifier& identifier)
	{
		out << '`';

		if (identifier.isAbsolute())
			out << "::";

		bool isFirst = true;

		for (const auto& part : identifier)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else {
				out << "::";
			}

			out << part.text();
		}

		out << '`';

		return out;
	}
}
