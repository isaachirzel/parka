#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Identifier.hpp"

namespace parka
{
	QualifiedIdentifier::QualifiedIdentifier(Array<Identifier>&& parts, bool isAbsolute) :
	_parts(std::move(parts)),
	_isAbsolute(isAbsolute)
	{
		assert(_parts.length() > 0);
	}

	static bool parseAbsolute(Token& token)
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();
		return true;
	}

	Optional<QualifiedIdentifier> QualifiedIdentifier::parse(Token& token)
	{
		auto isAbsolute = parseAbsolute(token);
		auto parts = Array<Identifier>(8);
		
		while (true)
		{
			auto identifier = Identifier::parse(token);

			if (!identifier)
				return {};

			parts.push(*identifier);

			if (token.type() == TokenType::Scope)
			{
				token.increment();
				continue;
			}

			break;
		}

		auto qualifiedIdentifier = QualifiedIdentifier(std::move(parts), isAbsolute);

		return qualifiedIdentifier;
	}

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
