// local headers
#include <warbler/tokenizer.h>

// standard headers
#include <assert.h>

const char *src =
"func this_is_a_long_function_name(num: i32) -> i32		\n"\
"{														\n"\
"var foo = bar(.53, 6) * 12.6 + 4						\n"\
"														\n"\
"}														\n";

int main(void)
{
	Error error;

	if ((error = tokenizer_init()))
		return error;

	HxArray *tokens;
	if ((error = tokenize(&tokens, "in-memory-file", src)))
	{
		tokenizer_free();
		return error;
	}

	printf("Length: %zu\n", hxarray_length(tokens));

	for (size_t i = 0; i < hxarray_length(tokens); ++i)
	{
		printf("%zu: ", i);
		token_println(hxarray_at(tokens, i));
	}

	assert(hxarray_length(tokens) == 25);
	Token *ptr = hxarray_at(tokens, 0);

	assert(ptr[0].type == TOKEN_FUNC);
	assert(ptr[1].type == TOKEN_IDENTIFIER);
	assert(ptr[2].type == TOKEN_LPAREN);
	assert(ptr[3].type == TOKEN_IDENTIFIER);
	assert(ptr[4].type == TOKEN_COLON);
	assert(ptr[5].type == TOKEN_IDENTIFIER);
	assert(ptr[6].type == TOKEN_RPAREN);
	assert(ptr[7].type == TOKEN_SINGLE_ARROW);
	assert(ptr[8].type == TOKEN_IDENTIFIER);
	assert(ptr[9].type == TOKEN_LBRACE);
	assert(ptr[10].type == TOKEN_VAR);
	assert(ptr[11].type == TOKEN_IDENTIFIER);
	assert(ptr[12].type == TOKEN_ASSIGN);
	assert(ptr[13].type == TOKEN_IDENTIFIER);
	assert(ptr[14].type == TOKEN_LPAREN);
	assert(ptr[15].type == TOKEN_FLOAT_LITERAL);
	assert(ptr[16].type == TOKEN_COMMA);
	assert(ptr[17].type == TOKEN_INTEGER_LITERAL);
	assert(ptr[18].type == TOKEN_RPAREN);
	assert(ptr[19].type == TOKEN_ASTERISK);
	assert(ptr[20].type == TOKEN_FLOAT_LITERAL);
	assert(ptr[21].type == TOKEN_PLUS);
	assert(ptr[22].type == TOKEN_INTEGER_LITERAL);
	assert(ptr[23].type == TOKEN_RBRACE);
	assert(ptr[24].type == TOKEN_END_OF_FILE);

	return 0;
}
