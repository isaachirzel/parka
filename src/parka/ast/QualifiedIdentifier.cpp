#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Identifier.hpp"

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
