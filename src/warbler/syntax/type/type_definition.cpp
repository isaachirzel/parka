#include <warbler/syntax//type/type_definition.hpp>

#include <warbler/util/print.hpp>

#include <warbler/syntax//type/struct.hpp>

namespace warbler::syntax
{
	Result<Ptr<TypeDefinition>> TypeDefinition::parse(TokenIterator& iter)
	{
		// skip 'type' keyword
		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
		{
			parse_error(iter, "type identifier");
			return {};
		}

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after type name");
			return {};
		}

		iter += 1;

		switch (iter->type())
		{
			case TOKEN_STRUCT:
			{
				auto res = Struct::parse(iter, name.unwrap());

				if (!res)
					return {};

				auto *ptr = new Struct(res.unwrap());

				return Ptr<TypeDefinition>(ptr);
			}

			default:
				#pragma message("Implement the ability to have other types as type definitions")
				parse_error(iter, "type definition or base type");
				return {};
		}
	}
}
