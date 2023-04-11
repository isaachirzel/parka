#include "parka/symbol/Identifier.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<Identifier> Identifier::parse(Token& token)
	{
		if (token.type() != TokenType::Identifier)
		{
			printParseError(token, "identifier");
			return {};
		}

		auto identifier = Identifier(token);

		token.increment();

		return identifier;
	}

	std::ostream& operator<<(std::ostream& out, const Identifier& identifier)
	{
		out << '`' << identifier.text() << '`';

		return out;
	}
}
