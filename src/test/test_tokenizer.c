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
		token_println(tokens.buffer + i);
	}

	assert(tokens.buffer[0].type == TOKEN_FUNC);
	assert(tokens.buffer[1].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[2].type == TOKEN_LPAREN);
	assert(tokens.buffer[3].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[4].type == TOKEN_COLON);
	assert(tokens.buffer[5].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[6].type == TOKEN_RPAREN);
	assert(tokens.buffer[7].type == TOKEN_SINGLE_ARROW);
	assert(tokens.buffer[8].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[9].type == TOKEN_LBRACE);
	assert(tokens.buffer[10].type == TOKEN_VAR);
	assert(tokens.buffer[11].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[12].type == TOKEN_ASSIGN);
	assert(tokens.buffer[13].type == TOKEN_IDENTIFIER);
	assert(tokens.buffer[14].type == TOKEN_LPAREN);
	assert(tokens.buffer[15].type == TOKEN_FLOAT_LITERAL);
	assert(tokens.buffer[16].type == TOKEN_COMMA);
	assert(tokens.buffer[17].type == TOKEN_INTEGER_LITERAL);
	assert(tokens.buffer[18].type == TOKEN_RPAREN);
	assert(tokens.buffer[19].type == TOKEN_ASTERISK);
	assert(tokens.buffer[20].type == TOKEN_FLOAT_LITERAL);
	assert(tokens.buffer[21].type == TOKEN_PLUS);
	assert(tokens.buffer[22].type == TOKEN_INTEGER_LITERAL);
	assert(tokens.buffer[23].type == TOKEN_RBRACE);
	assert(tokens.buffer[24].type == TOKEN_END_OF_FILE);

	return 0;
}
