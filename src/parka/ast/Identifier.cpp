#include "parka/symbol/Identifier.hpp"
#include "parka/Token.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Identifier::Identifier(const Token& token) :
	_token(token),
	_text(token.text())
	{}

	Optional<Identifier> Identifier::parse(Token& token)
	{
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "identifier");
			return {};
		}

		auto identifier = Identifier(token);

		token.increment();

		return identifier;
	}

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
