#include <warbler/tokenizer.h>

// local includes
#include <warbler/error.h>

namespace warbler
{
	struct SourceLocation
	{
		const char *pos;
		size_t line;
		size_t col;
	};

	Tokenizer::Tokenizer() :
	_token_types({
		// misc keywords
		{ "func", Token::Type::FUNC },
		{ "var", Token::Type::VAR },
		{ "type", Token::Type::TYPE },
		{ "return", Token::Type::RETURN },
		{ "for", Token::Type::FOR },
		{ "while", Token::Type::WHILE },
		{ "loop", Token::Type::LOOP },
		{ "continue", Token::Type::CONTINUE },
		{ "break", Token::Type::BREAK },
		{ "if", Token::Type::IF },
		{ "else", Token::Type::ELSE },
		{ "switch", Token::Type::SWITCH },
		{ "case", Token::Type::CASE },

		// typenames
		{ "struct", Token::Type::STRUCT },
		{ "union", Token::Type::UNION },
		{ "enum", Token::Type::ENUM },
		{ "true", Token::Type::TRUE },
		{ "false", Token::Type::FALSE },
		{ ":", Token::Type::COLON },

		// separators
		{ "(", Token::Type::LPAREN },
		{ ")", Token::Type::RPAREN },
		{ "[", Token::Type::LBRACK },
		{ "]", Token::Type::RBRACK },
		{ "{", Token::Type::LBRACE },
		{ "}", Token::Type::RBRACE },
		{ ".", Token::Type::DOT },
		{ ",", Token::Type::COMMA },
		{ ";", Token::Type::SEMICOLON },

		// unary operators
		{ "++", Token::Type::INCREMENT },
		{ "--", Token::Type::DECREMENT },

		// binary operators
		{ "*",  Token::Type::ASTERISK },
		{ "/",  Token::Type::SLASH },
		{ "+",  Token::Type::PLUS },
		{ "-",  Token::Type::MINUS },
		{ "<",  Token::Type::LANGBRACK },
		{ ">",  Token::Type::RANGBRACK },
		{ "&",  Token::Type::AMPERSAND },
		{ "|",  Token::Type::PIPELINE },
		{ "^",  Token::Type::CARROT },
		{ "**", Token::Type::POW },
		{ "&&", Token::Type::AND },
		{ "||", Token::Type::OR },
		{ "==", Token::Type::EQUALS },
		{ "!=", Token::Type::NEQUALS },
		{ ">=", Token::Type::GTOET },
		{ "<=", Token::Type::LTOET },
		{ ">>", Token::Type::RSHIFT },
		{ "<<", Token::Type::LSHIFT },
		{ "->", Token::Type::SINGLE_ARROW },
		{ "=>", Token::Type::DOUBLE_ARROW },

		// assign operators
		{ "=",  Token::Type::ASSIGN },
		{ "+=", Token::Type::ADD_ASSIGN },
		{ "+=", Token::Type::ADD_ASSIGN },
		{ "-=", Token::Type::SUB_ASSIGN },
		{ "*=", Token::Type::MUL_ASSIGN },
		{ "/=", Token::Type::DIV_ASSIGN },
		{ "%=", Token::Type::MOD_ASSIGN },

		// modules
		{ "import", Token::Type::IMPORT },
		{ "export", Token::Type::EXPORT },
		{ "::", Token::Type::SCOPE }
	})
	{
		// setting up identifier characters
		_char_types['_'] = CharType::IDENTIFIER;
		for (size_t i = 'a'; i <= 'z'; ++i)
			_char_types[i] = CharType::IDENTIFIER;
		for (size_t i = 'A'; i <= 'Z'; ++i)
			_char_types[i] = CharType::IDENTIFIER;
		for (size_t i = '0'; i <= '9'; ++i)
			_char_types[i] = CharType::DIGIT;

		// setting up separator characters
		_char_types['('] = CharType::SEPARATOR;
		_char_types[')'] = CharType::SEPARATOR;
		_char_types['['] = CharType::SEPARATOR;
		_char_types[']'] = CharType::SEPARATOR;
		_char_types['{'] = CharType::SEPARATOR;
		_char_types['}'] = CharType::SEPARATOR;
		_char_types[';'] = CharType::SEPARATOR;
		_char_types[','] = CharType::SEPARATOR;

		// dot character
		_char_types['.'] = CharType::DOT;

		// setting up operator characters
		_char_types['!'] = CharType::OPERATOR;
		_char_types['@'] = CharType::OPERATOR;
		_char_types['#'] = CharType::OPERATOR;
		_char_types['$'] = CharType::OPERATOR;
		_char_types['%'] = CharType::OPERATOR;
		_char_types['^'] = CharType::OPERATOR;
		_char_types['&'] = CharType::OPERATOR;
		_char_types['*'] = CharType::OPERATOR;
		_char_types['-'] = CharType::OPERATOR;
		_char_types['='] = CharType::OPERATOR;
		_char_types['|'] = CharType::OPERATOR;
		_char_types['+'] = CharType::OPERATOR;
		_char_types['<'] = CharType::OPERATOR;
		_char_types['>'] = CharType::OPERATOR;
		_char_types['?'] = CharType::OPERATOR;
		_char_types['/'] = CharType::OPERATOR;
		_char_types[':'] = CharType::OPERATOR;

		// setting literal types
		_char_types['\''] = CharType::QUOTE;
		_char_types['\"'] = CharType::QUOTE;
	}

	void get_next_token_pos(SourceLocation& location)
	{
		while (*location.pos)
		{
			if (*location.pos > ' ')
				break;
			
			if (*location.pos == '\n')
			{
				++location.line;
				location.col = 0;
			}

			++location.col;
			++location.pos;
		}
	}

	Token get_identifier_token(SourceLocation& location)
	{

	}

	Token get_next_token(SourceLocation& location, const Tokenizer& tokenizer)
	{
		get_next_token_pos(location);

		if (*location->pos == 0)
		{
			Token out =
			{
				.str = (String)
				{
					.ptr = NULL,
					.len = 0
				},
				.line = location->line,
				.col = location->col,
				.type = Token::Type::EOF
			};

			return out;
	}

	Token get_next_token(SourceLocation *location)
	{
		get_next_token_pos(location);

		if (*location->pos == 0)
			return {};

	// 	Token out = {
	// 		.line = location.line,
	// 		.col = location.col,
	// 		.type = Token::Type::ERROR,
	// 		.out = (String)
	// 		{
	// 			.ptr = location.pos,
	// 			.len = 0
	// 		}
	// 	};
		
	// 	char type = char_types[*location->pos];
	// 	++location->pos;

	// 	switch (type)
	// 	{
	// 		case CharType::IDENTIFIER:

	// 	}

	// 	switch (type)
	// 	{
	// 		case CharType::IDENTIFIER:;
	// 			char curr_type = char_types[*pos];
	// 			while (curr_type == CharType::IDENTIFIER || curr_type == CharType::DIGIT)
	// 			{
	// 				++pos;
	// 				curr_type = char_types[*pos];
	// 			}
	// 			out.str.len = pos - out.str.ptr;

	// 			// slight optimization as most keywords and operators are short
	// 			if (out.str.len > MAX_KEYWORD_LENGTH)
	// 			{
	// 				out.type = Token::Type::IDENTIFIER;
	// 				goto finish;
	// 			}

	// 			// else table lookup
	// 			goto table_lookup;
				
	// 		case CharType::SEPARATOR:
	// 			out.type = char_token_types[*out.str.ptr];
	// 			out.str.len = 1;
	// 			goto finish;

	// 		case CharType::DOT:
	// 			if (char_types[*pos] == CharType::DIGIT)
	// 			{
	// 				out.type = Token::Type::FLOAT_LITERAL;
	// 				goto float_literal;
	// 			}
	// 			while (char_types[*pos] == CharType::DOT) ++pos;
	// 			out.str.len = pos - out.str.ptr;
	// 			out.type = Token::Type::DOT + out.str.len - 1;
	// 			if (out.str.len > 3) out.type = Token::Type::ERROR;
	// 			goto finish;

	// 		case CharType::OPERATOR:

	// 			while (char_types[*pos] == CharType::OPERATOR) ++pos;
	// 			out.str.len = pos - out.str.ptr;
	// 			if (out.str.len == 1)
	// 			{
	// 				out.type = char_token_types[*out.str.ptr];
	// 				goto finish;
	// 			}
	// 			goto table_lookup;


	// 		float_literal:
	// 		case CharType::DIGIT:
	// 			while (*pos)
	// 			{
	// 				// if encounters a dot
	// 				if (pos[0] == '.')
	// 				{	
	// 					// range or elipsis
	// 					if (pos[1] == '.') break;

	// 					// if multiple dots, flag float or error
	// 					if (!out.type) out.type = Token::Type::FLOAT_LITERAL;
	// 					else out.type = Token::Type::ERROR;

	// 					pos += 1;
	// 					continue;
	// 				}
	// 				// if encountering non digit/dot
	// 				if (char_types[*pos] != CharType::DIGIT) break;
	// 				pos += 1;
	// 			}
	// 			out.str.len = pos - out.str.ptr;
	// 			if (!out.type) out.type = Token::Type::INT_LITERAL;

	// 			goto finish;

	// 		case CharType::QUOTE:
	// 			// got till non-escaped end of string
	// 			while (pos[0] != out.str.ptr[0] && pos[-1] != '\\') ++pos;
	// 			++out.str.ptr;
	// 			out.str.len = pos - out.str.ptr;
	// 			++pos;
	// 			if (out.str.ptr[-1] == '\'')
	// 			{
	// 				out.type = Token::Type::CharType::LITERAL;
	// 			}
	// 			else if (out.str.ptr[-1] == '\"')
	// 			{
	// 				out.type = Token::Type::STR_LITERAL;
	// 			}
	// 			goto finish;

	// 		default:
	// 			out.str.len = 1;
	// 			out.type = Token::Type::ERROR;
	// 			goto finish;
	// 	}

		
	// finish:
	// 	*src = pos;
	// 	return out;

	// table_lookup:;
	// 	char tmp[MAX_KEYWORD_LENGTH + 1];

	// 	// table lookup
	// 	for (int i = 0; i < out.str.len; ++i)
	// 	{
	// 		tmp[i] = out.str.ptr[i];
	// 	}

	// 	tmp[out.str.len] = 0;
	// 	out.type = chartbl_get(token_types, tmp);

	// 	// if it failed to find matching key
	// 	if (out.type == 0)
	// 	{
	// 		if (type == CharType::IDENTIFIER)
	// 		{
	// 			out.type = Token::Type::IDENTIFIER;
	// 		}
	// 		else
	// 		{
	// 			out.type = Token::Type::ERROR;
	// 		}
	// 	}

	// 	goto finish;
	// }

	std::vector<Token> Tokenizer::tokenize(const char *src) const
	{
		std::vector<Token> out;

		if (!out)
		{
			print_error("failed to allocate token list");
			return NULL;
		}

		SourceLocation location = {
			.pos = src,
			.line = 1,
			.col = 1
		};

		while (true)
		{
			Token token = get_next_token(&location);

			if (tok.type == Token::Type::ERROR)
			{
				print_error("token error");
				destroyHxArray(out);
				return NULL;
			}

			pushHxArray(out, &token);

			if (token.type == Token::Type::EOF)
				break;
		}

		return out;
	}
}