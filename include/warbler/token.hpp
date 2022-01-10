#ifndef WARBLER_TOKEN_HPP
#define WARBLER_TOKEN_HPP

// local includes
#include <warbler/primitive.hpp>

// standard headers
#include <vector>

namespace warbler
{
	enum TokenType
	{
		TOKEN_END_OF_FILE,
		TOKEN_IDENTIFIER,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACK,
		TOKEN_RBRACK,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_LANGBRACK,
		TOKEN_RANGBRACK,
		TOKEN_SEMICOLON,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_DOT,
		TOKEN_ELIPSIS,
		TOKEN_AMPERSAND,
		TOKEN_PIPELINE,
		TOKEN_CARROT,
		TOKEN_LSHIFT,
		TOKEN_RSHIFT,
		TOKEN_BOOLEAN_NOT,
		TOKEN_BOOLEAN_AND,
		TOKEN_BOOLEAN_OR,
		TOKEN_XOR,
		TOKEN_NOT,
		TOKEN_EQUALS,
		TOKEN_NOT_EQUALS,
		TOKEN_LESS,
		TOKEN_GREATER,
		TOKEN_LESS_EQUALS,
		TOKEN_GREATER_EQUALS,
		TOKEN_SINGLE_ARROW,
		TOKEN_DOUBLE_ARROW,
		TOKEN_OPTION,
		TOKEN_QUESTION,
		// assign tokens
		TOKEN_ASSIGN,
		TOKEN_BECOME_ASSIGN,
		TOKEN_ADD_ASSIGN,
		TOKEN_SUBTRACT_ASSIGN,
		TOKEN_MULTIPLY_ASSIGN,
		TOKEN_DIVIDE_ASSIGN,
		TOKEN_MODULUS_ASSIGN,
		TOKEN_LSHIFT_ASSIGN,
		TOKEN_RSHIFT_ASSIGN,
		TOKEN_BITAND_ASSIGN,
		TOKEN_BITOR_ASSIGN,
		TOKEN_BITXOR_ASSIGN,

		TOKEN_MODULUS,
		TOKEN_SLASH,
		TOKEN_ASTERISK,
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_POW,
		TOKEN_INCREMENT,
		TOKEN_DECREMENT,
		// literal
		TOKEN_INTEGER_LITERAL,
		TOKEN_FLOAT_LITERAL,
		TOKEN_HEXADECIMAL_LITERAL,
		TOKEN_BINARY_LITERAL,
		TOKEN_OCTAL_LITERAL,
		TOKEN_CHAR_LITERAL,
		TOKEN_STRING_LITERAL,
		TOKEN_TRUE,
		TOKEN_FALSE,
		TOKEN_VAR,
		TOKEN_FUNC,
		TOKEN_RETURN,
		TOKEN_FOR,
		TOKEN_WHILE,
		TOKEN_LOOP,
		TOKEN_CONTINUE,
		TOKEN_BREAK,
		TOKEN_IF,
		TOKEN_ELSE,
		TOKEN_SWITCH,
		TOKEN_CASE,
		TOKEN_TYPE,
		TOKEN_STRUCT,
		TOKEN_ENUM,
		TOKEN_UNION,
		TOKEN_IMPORT,
		TOKEN_EXPORT,
		TOKEN_SCOPE,
		TOKEN_COUNT
	};

	struct Token
	{
	private:

		StringView _text;
		const String& _filename;
		usize _line;
		usize _col;
		TokenType _type;
	
	public:

		Token();
		Token(const StringView& text, const String& filename, usize line, usize col, TokenType type);

		const String& text() const { return _text; }
		const String& filename() const { return _filename; }
		usize line() const { return _line; }
		usize col() const { return _col; }
		TokenType type() const { return _type; }
	};

	typedef std::vector<Token>::const_iterator TokenIterator;

	Token token_default();
	Token token_initial(const char *filename, const char *src);
	Token token_eof();
	void token_print(const Token *token);
	void token_println(const Token *token);
}
#endif
