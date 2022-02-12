// local headers
#include <warbler/tokenizer.hpp>

// standard headers
#include <assert.h>

const char *src =
"func this_is_a_long_function_name(num: i32) -> i32		\n"\
"{														\n"\
"var foo = bar(.53, 6) * 12.6 + 4;						\n"\
"														\n"\
"}														\n";

using namespace warbler;

int main(void)
{
	tokenizer_init();

	auto res = tokenize("<in-memory-file>", src);

	if (!res)
		return {};

	auto tokens = res.unwrap();

	printf("Length: %zu\n", tokens.size());

	std::cout << "size: " << tokens.size() << std::endl;

	assert(tokens.size() == 26);
	for (size_t i = 0; i < tokens.size(); ++i)
	{
		std::cout << i << ": " << tokens[i] << std::endl;
	}

	assert(tokens[0].type() == TOKEN_FUNC);
	assert(tokens[1].type() == TOKEN_IDENTIFIER);
	assert(tokens[2].type() == TOKEN_LPAREN);
	assert(tokens[3].type() == TOKEN_IDENTIFIER);
	assert(tokens[4].type() == TOKEN_COLON);
	assert(tokens[5].type() == TOKEN_IDENTIFIER);
	assert(tokens[6].type() == TOKEN_RPAREN);
	assert(tokens[7].type() == TOKEN_SINGLE_ARROW);
	assert(tokens[8].type() == TOKEN_IDENTIFIER);
	assert(tokens[9].type() == TOKEN_LBRACE);
	assert(tokens[10].type() == TOKEN_VAR);
	assert(tokens[11].type() == TOKEN_IDENTIFIER);
	assert(tokens[12].type() == TOKEN_ASSIGN);
	assert(tokens[13].type() == TOKEN_IDENTIFIER);
	assert(tokens[14].type() == TOKEN_LPAREN);
	assert(tokens[15].type() == TOKEN_FLOAT_LITERAL);
	assert(tokens[16].type() == TOKEN_COMMA);
	assert(tokens[17].type() == TOKEN_INTEGER_LITERAL);
	assert(tokens[18].type() == TOKEN_RPAREN);
	assert(tokens[19].type() == TOKEN_ASTERISK);
	assert(tokens[20].type() == TOKEN_FLOAT_LITERAL);
	assert(tokens[21].type() == TOKEN_PLUS);
	assert(tokens[22].type() == TOKEN_INTEGER_LITERAL);
	assert(tokens[23].type() == TOKEN_SEMICOLON);
	assert(tokens[24].type() == TOKEN_RBRACE);
	assert(tokens[25].type() == TOKEN_END_OF_FILE);

	return 0;
}
