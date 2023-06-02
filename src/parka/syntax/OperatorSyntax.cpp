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

		Log::notImplemented(here());
	}

	bool validate(const EntitySyntaxId&)
	{
		Log::notImplemented(here());
	}
}
