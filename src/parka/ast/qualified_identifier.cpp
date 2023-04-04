#include "parka/ast/qualified_identifier.hpp"
#include "parka/ast/identifier.hpp"

bool parseAbsolute(Token& token)
{
	if (token.type() == TokenType::Scope)
	{
		token.increment();
		return true;
	}

	return false;
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

		parts.push(identifier.unwrap());

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
