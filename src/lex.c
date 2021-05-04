#include <lex.h>

char char_types[128];
const char *tokens[] = {
	"int"
};

void lex_init()
{

}

TokenList *lex(const char *src)
{

}

TokenList *token_list_create()
{
	TokenList* out = malloc(sizeof(TokenList));
	if (!out) return NULL;

	out->toks = malloc(1);
	if (!out->toks) {
		free(out);
		return NULL;
	}

	out->len = 0;

	return out;
}

void token_list_push(TokenList *list, Token t)
{
	list->len += 1;
	Token *tmp = realloc(list->len * sizeof(Token));
	if (!tmp) abort();
	list->toks = tmp;
}
