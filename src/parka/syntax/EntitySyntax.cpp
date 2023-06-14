#include "parka/syntax/EntitySyntax.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const EntitySyntax& syntax)
	{
		out << syntax.identifier() << ": " << syntax.entityType();

		return out;
	}
}
