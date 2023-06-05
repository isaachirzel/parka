#include "parka/syntax/StructSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/MemberSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<EntitySyntaxId> StructSyntax::parse(Token& token)
	{
		auto keyword = KeywordSyntax::parseStruct(token);

		if (!keyword)
			return {};

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::LeftBrace)
		{
			// TODO: 
			log::parseError(token, "'{' before member list", "Bodyless structs are not allowed.");
			return {};
		}

		auto members = Array<MemberSyntax>();

		token.increment();

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = MemberSyntax::parse(token);

				if (!member)
					return {};

				members.push(*member);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightBrace)
			{
				log::parseError(token, "'}' after struct body");
				return {};
			}
		}

		token.increment();

		auto strct = StructSyntax(*identifier, std::move(members));
		auto id = EntitySyntaxId::create(std::move(strct));

		return id;
	}

	// bool StructSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	bool success = true;

	// 	usize index = 0;

	// 	for (auto& member : _members)
	// 	{
	// 		for (usize j = 0; j < index; ++j)
	// 		{
	// 			const auto& previous = _members[j];

	// 			if (member.name() == previous.name())
	// 			{
	// 				success = false;
					
	// 				log::errorprintError(member.name(), "A member with same name is already declared in this struct.");
	// 				log::parseError(previous.name(), "Previous delcaration here.");

	// 				break;
	// 			}
	// 		}

	// 		if (member.validate(functionId))
	// 			success = false;

	// 		index += 1;
	// 	}

	// 	return success;
	// }
}
