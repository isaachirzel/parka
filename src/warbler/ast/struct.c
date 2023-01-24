#include "warbler/ast/struct.h"
#include "warbler/symbol_table.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parseStruct(usize *out, Token *token, const char *package)
{
	assert(token->type == TOKEN_KEYWORD_STRUCT);

	usize index = symbolTableAddStruct();
	Struct *node = symbolTableGetStruct(index);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "struct name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbol(package, token);

	incrementToken(token);

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

void structFree(Struct *node)
{
	memberListFree(&node->members);

	deallocate(node->symbol);
}
