#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	bool IdentifierAst::operator==(const IdentifierAst& other) const
	{
		return _text == other._text;
	}

	std::ostream& operator<<(std::ostream& out, const IdentifierAst& identifier)
	{
		out << identifier.text();

		return out;
	}
}
