#include "parka/ast/Struct.hpp"
#include "parka/ast/Member.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Package.hpp"

namespace parka::ast
{
	StructAst *StructAst::parse(Token &token)
	{
		auto keyword = KeywordAst::parseStruct(token);

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

		auto members = Array<MemberAst*>();

		token.increment();

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = MemberAst::parse(token);

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

		auto snippet = keyword->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new StructAst(snippet, *identifier, std::move(members));

		return syntax;
	}

	bool StructAst::declare(EntityAst& entity)
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

	bool StructAst::declareSelf(PackageAst& parent)
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

	SymbolTableEntry *StructAst::find(const Identifier& identifier)
	{
		auto *result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	ir::EntityIr *StructAst::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent->resolve(identifier);
	}

	ir::StructIr *StructAst::validate()
	{
		log::notImplemented(here());
	}

	String StructAst::getSymbol() const
	{
		auto symbol = _parent->getSymbol();

		symbol += "::";
		symbol += name();

		return symbol;
	}

	// bool StructAst::validate(const EntityAst& function)
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
	// 			friend std::ostream& operator<<(std::ostream& out, const StructAst& syntax);	success = false;
					
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

	std::ostream& operator<<(std::ostream& out, const StructAst& syntax)
	{
		out << "struct " << syntax._identifier << " {}";

		return out;
	}
}
