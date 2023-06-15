#include "parka/ast/Struct.hpp"
#include "parka/ast/Member.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Package.hpp"

namespace parka
{
	StructContext::StructContext(String&& symbol) :
	_symbol(std::move(symbol))
	{}

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

	bool StructSyntax::declare(EntitySyntax& entity)
	{
		// TODO: Token snippet
		const auto& name = entity.name();
		auto isDeclared = _symbols.insert(name, &entity);

		if (!isDeclared)
		{
			log::error("Member `$` has already been declared in struct $.", name, _identifier);
		}

		return isDeclared;
	}

	bool StructSyntax::declareSelf(PackageSyntax& parent)
	{
		_parent = &parent;

		bool success = _parent->declare(*this);

		for (auto *member : _members)
		{
			if (!member->declareSelf(*this))
				success = false;
				// TODO: Previous delcaration
		}

		return success;
	}

	EntityEntry *StructSyntax::find(const Identifier& identifier)
	{
		log::notImplemented(here());
	}

	EntityContext *StructSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		log::notImplemented(here());
	}

	StructContext *StructSyntax::validate()
	{
		log::notImplemented(here());
	}

	String StructSyntax::getSymbol() const
	{
		auto symbol = _parent->getSymbol();

		symbol += "::";
		symbol += name();

		return symbol;
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
