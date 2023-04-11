#include "parka/syntax/StringLiteralSyntax.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> StringLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			printParseError(token, "string");
			return {};
		}

		auto literal = StringLiteralSyntax(token, token.text());
		auto id = Storage::add(std::move(literal));

		token.increment();

		return id;
	}

	// bool StringLiteralSyntax::validate(const EntitySyntaxId&)
	// {
	// 	return true;
	// }

	// Optional<Type> StringLiteralSyntax::getType() const
	// {
	// 	return Type::stringType;
	// }
}
