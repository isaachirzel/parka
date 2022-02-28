// local headers
#include <warbler/lexicon/tokenizer.hpp>

// standard headers
#include <assert.h>

const char *src = R"==(

function this_is_a_long_function_name(num: i32) -> i32
{
	var foo = bar(.53, 6) * 12.6 + 4;
}

)==";

using namespace warbler;

int main()
{
	// lexicon::init_tokenizer();

	// auto file = source::File::from(src);
	// auto res = lexicon::tokenize(file);

	// if (!res)
	// 	return 1;

	// auto tokens = res.unwrap();

	// printf("Length: %zu\n", tokens.size());

	// std::cout << "size: " << tokens.size() << std::endl;

	// assert(tokens.size() == 26);
	// for (size_t i = 0; i < tokens.size(); ++i)
	// {
	// 	std::cout << i << ": " << tokens[i] << std::endl;
	// }

	// assert(tokens[0].type() == source::TokenType::FUNC);
	// assert(tokens[1].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[2].type() == source::TokenType::LPAREN);
	// assert(tokens[3].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[4].type() == source::TokenType::Colon);
	// assert(tokens[5].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[6].type() == source::TokenType::RPAREN);
	// assert(tokens[7].type() == source::TokenType::SINGLE_ARROW);
	// assert(tokens[8].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[9].type() == source::TokenType::LBRACE);
	// assert(tokens[10].type() == source::TokenType::VAR);
	// assert(tokens[11].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[12].type() == source::TokenType::ASSIGN);
	// assert(tokens[13].type() == source::TokenType::IDENTIFIER);
	// assert(tokens[14].type() == source::TokenType::LPAREN);
	// assert(tokens[15].type() == source::TokenType::FLOAT_LITERAL);
	// assert(tokens[16].type() == source::TokenType::Comma);
	// assert(tokens[17].type() == source::TokenType::INTEGER_LITERAL);
	// assert(tokens[18].type() == source::TokenType::RPAREN);
	// assert(tokens[19].type() == source::TokenType::ASTERISK);
	// assert(tokens[20].type() == source::TokenType::FLOAT_LITERAL);
	// assert(tokens[21].type() == source::TokenType::PLUS);
	// assert(tokens[22].type() == source::TokenType::INTEGER_LITERAL);
	// assert(tokens[23].type() == source::TokenType::SEMICOLON);
	// assert(tokens[24].type() == source::TokenType::RightBrace);
	// assert(tokens[25].type() == source::TokenType::END_OF_FILE);

	return 0;
}
