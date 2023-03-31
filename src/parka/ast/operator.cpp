#include "parka/ast/operator/operator.hpp"
#include "parka/util/print.hpp"

Optional<Operator> parse(Token& token)
{
	if (token.type() != TokenType::KeywordOperator)
	{
		printParseError(token, "`operator`");
	}

	exitNotImplemented(here());
}

bool validate(SymbolTable& symbols)
{
	exitNotImplemented(here());
}
