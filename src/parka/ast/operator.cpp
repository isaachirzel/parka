#include "parka/ast/operator/operator.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/util/print.hpp"

Optional<Operator> parse(Token& token)
{
	auto keyword = Keyword::parseOperator(token);

	if (!keyword)
		return {};

	exitNotImplemented(here());
}

bool validate(const EntityId&)
{
	exitNotImplemented(here());
}
