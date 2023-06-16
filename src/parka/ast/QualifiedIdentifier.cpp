#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Identifier.hpp"

namespace parka::ast
{
	static bool parseAbsolute(Token& token)
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();
		return true;
	}

	Optional<QualifiedIdentifier> QualifiedIdentifier::parse(Token& token)
	{
		auto start = Snippet(token);
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

		// Parts is guaranteed to be at least 1 long
		auto snippet = start + parts.back().snippet();
		auto qualifiedIdentifier = QualifiedIdentifier(snippet, std::move(parts), isAbsolute);

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
