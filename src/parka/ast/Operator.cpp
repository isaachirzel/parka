#include "parka/ast/Operator.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	Optional<Operator> parse(Token& token)
	{
		auto keyword = KeywordAst::parseOperator(token);

		if (!keyword)
			return {};

		log::notImplemented(here());
	}
}
