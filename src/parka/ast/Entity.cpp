#include "parka/ast/Entity.hpp"

namespace parka::ast
{
	std::ostream& operator<<(std::ostream& out, const EntityAst& syntax)
	{
		out << syntax.name() << ": " << syntax.entityType;

		return out;
	}	
}
