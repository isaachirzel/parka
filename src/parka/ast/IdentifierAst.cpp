#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	bool Identifier::operator==(const Identifier& other) const
	{
		return _text == other._text;
	}

	std::ostream& operator<<(std::ostream& out, const Identifier& identifier)
	{
		out << '`' << identifier.text() << '`';

		return out;
	}
}
