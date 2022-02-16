#include <warbler/ast/type/type_definition.hpp>

#include <warbler/print.hpp>
#include <warbler/ast/type/struct.hpp>

namespace warbler::ast
{
	Result<Ptr<TypeDefinition>> TypeDefinition::parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_STRUCT:
			{
				auto res = Struct::parse(iter);

				if (!res)
					return {};

				return Ptr<TypeDefinition> { new Struct { res.unwrap() } };
			}

			default:
				parse_error(iter, "type definition");
				return {};
		}
	}
}
