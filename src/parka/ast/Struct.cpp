#include "parka/ast/Struct.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Package.hpp"

namespace parka
{
	StructSyntax::StructSyntax(Identifier&& identifier, Array<MemberSyntax*>&& members) :
	_identifier(std::move(identifier)),
	_members(std::move(members)),
	_symbols(),
	_parent(nullptr),
	_context(nullptr)
	{}

	StructSyntax *StructSyntax::parse(Token &token)
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

		auto members = Array<MemberSyntax*>();

		token.increment();

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = MemberSyntax::parse(token);

				if (!member)
					return {};

				members.push(member);

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

		auto *syntax = new StructSyntax(*identifier, std::move(members));

		return syntax;
	}

	void StructSyntax::declare(SymbolTable& parent)
	{
		_parent = &parent;

		for (auto *member : _members)
		{
			const auto& name = member->name();
			const auto result = _symbols.insert(name, member);

			if (!result)
				log::error(member->token(), "Member `$` has already been declared in struct ``.", name, _identifier);
				// TODO: Previous delcaration
		}
	}

	StructContext *StructSyntax::validate()
	{
		log::notImplemented(here());
	}

	// bool StructSyntax::validate(const EntitySyntax& function)
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
	// 			friend std::ostream& operator<<(std::ostream& out, const StructSyntax& syntax);	success = false;
					
	// 				log::errorprintError(member.name(), "A member with same name is already declared in this struct.");
	// 				log::parseError(previous.name(), "Previous delcaration here.");

	// 				break;
	// 			}
	// 		}

	// 		if (member.validate(function))
	// 			success = false;

	// 		index += 1;
	// 	}

	// 	return success;
	// }

	std::ostream& operator<<(std::ostream& out, const StructSyntax& syntax)
	{
		out << "struct " << syntax._identifier << " {}";

		return out;
	}
}
