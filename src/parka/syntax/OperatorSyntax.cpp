#include "parka/syntax/OperatorSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<Operator> parse(Token& token)
	{
		auto keyword = KeywordSyntax::parseOperator(token);

		if (!keyword)
			return {};

		log::notImplemented(here());
	}

	bool validate(const EntitySyntaxId&)
	{
		log::notImplemented(here());
	}
}
