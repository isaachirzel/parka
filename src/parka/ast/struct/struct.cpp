#include "parka/ast/struct/struct.hpp"
#include "parka/ast/identifier.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/struct/member.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Struct::parse(Token& token)
{
	print("Parse struct");
	
	auto keyword = Keyword::parseStruct(token);

	if (!keyword)
		return {};

	auto identifier = Identifier::parse(token);

	if (!identifier)
		return {};

	if (token.type() != TokenType::LeftBrace)
	{
		// TODO: 
		printParseError(token, "'{' before member list", "Bodyless structs are not allowed.");
		return {};
	}

	auto members = Array<Member>();

	token.increment();

	if (token.type() != TokenType::RightBrace)
	{
		while (true)
		{
			auto member = Member::parse(token);

			if (!member)
				return {};

			members.push(member.unwrap());

			if (token.type() == TokenType::Comma)
			{
				token.increment();
				continue;
			}

			break;
		}

		if (token.type() != TokenType::RightBrace)
		{
			printParseError(token, "'}' after struct body");
			return {};
		}
	}

	token.increment();

	auto strct = Struct(identifier.unwrap(), std::move(members));
	auto id = NodeBank::add(std::move(strct));

	return id;
}

bool Struct::validate(const EntityId& functionId)
{
	bool success = true;

	usize index = 0;

	for (auto& member : _members)
	{
		for (usize j = 0; j < index; ++j)
		{
			const auto& previous = _members[j];

			if (member.name() == previous.name())
			{
				success = false;
				
				printError(member.name(), "A member with same name is already declared in this struct.");
				printNote(previous.name(), "Previous delcaration here.");

				break;
			}
		}

		if (member.validate(functionId))
			success = false;

		index += 1;
	}

	return success;
}
