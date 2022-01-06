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

	TokenArray tokens;
	if ((error = tokenize(&tokens, "in-memory-file", src)))
	{
		tokenizer_free();
		return error;
	}

	printf("Length: %zu\n", tokens.length);

	assert(tokens.length == 25);
	for (size_t i = 0; i < tokens.length; ++i)
	{
		printf("%zu: ", i);
		token_println(tokens.data + i);
	}

	assert(tokens.data[0].type == TOKEN_FUNC);
	assert(tokens.data[1].type == TOKEN_IDENTIFIER);
	assert(tokens.data[2].type == TOKEN_LPAREN);
	assert(tokens.data[3].type == TOKEN_IDENTIFIER);
	assert(tokens.data[4].type == TOKEN_COLON);
	assert(tokens.data[5].type == TOKEN_IDENTIFIER);
	assert(tokens.data[6].type == TOKEN_RPAREN);
	assert(tokens.data[7].type == TOKEN_SINGLE_ARROW);
	assert(tokens.data[8].type == TOKEN_IDENTIFIER);
	assert(tokens.data[9].type == TOKEN_LBRACE);
	assert(tokens.data[10].type == TOKEN_VAR);
	assert(tokens.data[11].type == TOKEN_IDENTIFIER);
	assert(tokens.data[12].type == TOKEN_ASSIGN);
	assert(tokens.data[13].type == TOKEN_IDENTIFIER);
	assert(tokens.data[14].type == TOKEN_LPAREN);
	assert(tokens.data[15].type == TOKEN_FLOAT_LITERAL);
	assert(tokens.data[16].type == TOKEN_COMMA);
	assert(tokens.data[17].type == TOKEN_INTEGER_LITERAL);
	assert(tokens.data[18].type == TOKEN_RPAREN);
	assert(tokens.data[19].type == TOKEN_ASTERISK);
	assert(tokens.data[20].type == TOKEN_FLOAT_LITERAL);
	assert(tokens.data[21].type == TOKEN_PLUS);
	assert(tokens.data[22].type == TOKEN_INTEGER_LITERAL);
	assert(tokens.data[23].type == TOKEN_RBRACE);
	assert(tokens.data[24].type == TOKEN_END_OF_FILE);

	return 0;
}
