#include "parka/syntax/OperatorSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<Operator> parse(Token& token)
	{
		auto keyword = KeywordSyntax::parseOperator(token);

		if (!keyword)
			return {};

		exitNotImplemented(here());
	}

	bool validate(const EntityId&)
	{
		exitNotImplemented(here());
	}
}
