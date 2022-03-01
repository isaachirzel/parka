#include <warbler/syntax/type/type_definition.hpp>

#include <warbler/util/print.hpp>

#include <warbler/syntax/type/struct.hpp>

namespace warbler::syntax
{
	Result<Ptr<TypeDefinition>> TypeDefinition::parse(lexicon::Token& token)
	{
		// skip 'type' keyword
		token.next();

		auto name = Identifier::parse(token.next());

		if (!name)
		{
			print_parse_error(token, "type identifier");
			return {};
		}

		if (token.type() != lexicon::TokenType::Colon)
		{
			print_parse_error(token, "':' after type name");
			return {};
		}

		token.next();

		switch (token.type())
		{
			case lexicon::TokenType::KeywordStruct:
			{
				auto res = Struct::parse(token, name.unwrap());

				if (!res)
					return {};

				auto *ptr = new Struct(res.unwrap());

				return Ptr<TypeDefinition>(ptr);
			}

			default:
				#pragma message "Implement the ability to have other types as type definitions"
				print_parse_error(token, "type definition or base type");
				return {};
		}
	}
}
