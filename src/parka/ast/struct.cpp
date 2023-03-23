#include "parka/ast/struct.hpp"
#include "parka/symbol_table.hpp"

#include "parka/util/print.hpp"

bool parseStruct(usize *out, Token& token, const char *package)
{
	assert(token.type() == TokenType::KeywordStruct);

	usize index = symbolTableAddStruct();
	Struct *node = symbolTableGetStruct(index);

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "struct name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbolKey(package, token);

	token.increment();

	if (!parseMemberList(&node->members, token))
		return false;

	*out = index;
	return true;
}

bool validateStruct(Struct *node, const Scope *packageScope)
{
	bool success = true;

	if (!validateMemberList(&node->members, packageScope))
		success = false;

	return success;
}
