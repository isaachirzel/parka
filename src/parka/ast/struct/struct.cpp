#include "parka/ast/struct/struct.hpp"
#include "parka/ast/struct/member.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Struct::parse(Token& token, const String& package)
{
	print("Parse struct");
	
	if (token.type() != TokenType::KeywordStruct)
	{
		printParseError(token, "`struct` keyword");
		return {};
	}

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "struct name", "Anonymous structs are not allowed.");
		return {};
	}

	auto name = token;
	auto symbol = package + "::" + name.text();

	token.increment();

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

	auto strct = Struct(name, std::move(symbol), std::move(members));
	auto id = NodeBank::add(std::move(strct));

	return id;
}

bool Struct::validate(LocalSymbolTable& symbols)
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

		if (member.validate(symbols))
			success = false;

		index += 1;
	}

	return success;
}
