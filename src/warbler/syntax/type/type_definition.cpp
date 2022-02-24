#include <warbler/syntax//type/type_definition.hpp>

#include <warbler/util/print.hpp>

#include <warbler/syntax//type/struct.hpp>

namespace warbler::syntax
{
	Result<Ptr<TypeDefinition>> TypeDefinition::parse(lexicon::TokenIterator& iter)
	{
		// skip 'type' keyword
		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
		{
			print_parse_error(iter, "type identifier");
			return {};
		}

		if (iter->type() != lexicon::TOKEN_COLON)
		{
			print_parse_error(iter, "':' after type name");
			return {};
		}

		iter += 1;

		switch (iter->type())
		{
			case TOKEN_KEYWORD_STRUCT:
			{
				auto res = Struct::parse(iter, name.unwrap());

				if (!res)
					return {};

				auto *ptr = new Struct(res.unwrap());

				return Ptr<TypeDefinition>(ptr);
			}

			default:
				#pragma message("Implement the ability to have other types as type definitions")
				print_parse_error(iter, "type definition or base type");
				return {};
		}
	}
}
