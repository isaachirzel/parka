#include <warbler/ast/expression/constant.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstring>

namespace warbler::ast
{
	Constant::Constant(String&& string) :
	_string(string),
	_type(CONSTANT_STRING)
	{}

	Constant::Constant(i64 integer) :
	_integer(integer),
	_type(CONSTANT_INTEGER)
	{}

	Constant::Constant(f64 floating) :
	_floating(floating),
	_type(CONSTANT_FLOAT)
	{}

	Constant::Constant(u32 character) :
	_character(character),
	_type(CONSTANT_CHARACTER)
	{}

	Constant::Constant(bool boolean) :
	_boolean(boolean),
	_type(CONSTANT_BOOLEAN)
	{}

	Constant::Constant(Constant&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case CONSTANT_CHARACTER:
				_character = other._character;
				break;

			case CONSTANT_STRING:
				new(&_string) auto(std::move(other._string));
				break;

			case CONSTANT_INTEGER:
				_integer = other._integer;
				break;

			case CONSTANT_FLOAT:
				_floating = other._floating;
				break;

			case CONSTANT_BOOLEAN:
				_boolean = other._boolean;
				break;
		}

		other._type = CONSTANT_INTEGER;
	}

	Constant::Constant(const Constant& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case CONSTANT_CHARACTER:
				_character = other._character;
				break;

			case CONSTANT_STRING:
				new(&_string) auto(other._string);
				break;

			case CONSTANT_INTEGER:
				_integer = other._integer;
				break;

			case CONSTANT_FLOAT:
				_floating = other._floating;
				break;

			case CONSTANT_BOOLEAN:
				_boolean = other._boolean;
				break;
		}
	}

	Constant::~Constant()
	{
		if (_type == CONSTANT_STRING)
			_string.~basic_string();
	}

	static inline u32 parse_character(const char *text)
	{
		#pragma message "Make sure character literals are only 1 long"
		return 0;
	}

	static f64 string_to_f64(const StringView& text)
	{
		f64 out = 0.0;

		for (size_t i = 0; i < text.size(); ++i)
		{
			if (text[i] != '.')
			{
				out = out * 10.0 + (text[i] - '0');
			}
			else
			{
				i += 1;

				f64 decimal = 0.0;
				f64 place = 1.0;

				while (i < text.length())
				{
					decimal = decimal * 10.0 + (text[i] - '0');
					place *= 10.0;
					++i;
				}
				
				out += (decimal / place);
				break;
			}
		}
		
		return out;
	}

	static i64 string_to_i64(const StringView& text)
	{
		i64 out = 0;

		for (size_t i = 0; i < text.size(); ++i)
			out = out * 10 + (text[i] - '0');

		return out;
	}

	static Constant parse_integer_literal(TokenIterator& iter, bool is_negative)
	{
		i64 value = string_to_i64(iter->text());

		if (is_negative)
			value = -value;

		iter += 1;

		return Constant(value);
	}

	static Constant parse_float_literal(TokenIterator& iter, bool is_negative)
	{
		f64 value = string_to_f64(iter->text());

		if (is_negative)
			value = -value;

		iter += 1;

		return Constant(value);
	}

	static Result<Constant> parse_number(TokenIterator& iter, bool is_negative)
	{
		switch (iter->type())
		{
			case TOKEN_INTEGER_LITERAL:
				return parse_integer_literal(iter, is_negative);				

			case TOKEN_FLOAT_LITERAL:
				return parse_float_literal(iter, is_negative);

			default:
				error_out(iter) << "expected number literal but got '" << *iter << '\'' << token_error(iter) << std::endl;
				return ERROR_ARGUMENT;
		}
	}

	Result<Constant> Constant::parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_MINUS:
				iter += 1;
				return parse_number(iter, true);
		
			case TOKEN_PLUS:
				iter += 1;
				return parse_number(iter, false);

			case TOKEN_INTEGER_LITERAL:
				return parse_integer_literal(iter, false);

			case TOKEN_FLOAT_LITERAL:
				return parse_float_literal(iter, false);

			case TOKEN_HEXADECIMAL_LITERAL:
				return not_implemented_error();

			case TOKEN_BINARY_LITERAL:
				return not_implemented_error();

			case TOKEN_OCTAL_LITERAL:
				return not_implemented_error();

			case TOKEN_CHAR_LITERAL:
				return not_implemented_error();

			case TOKEN_STRING_LITERAL:
			{
				String string = String(iter->text());
				iter += 1;
				return Constant(std::move(string));
			}

			case TOKEN_TRUE:
				iter += 1;
				return Constant(true);

			case TOKEN_FALSE:
				iter += 1;
				return Constant(false);

			default:
				break;
		}

		error_out(iter) << "expected constant but got '" << *iter << '\'' << token_error(iter) << std::endl;
		return ERROR_ARGUMENT;
	}

	void Constant::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);
		switch (_type)
		{
			case CONSTANT_CHARACTER:
				assert(false && "character print is not implemented");
				break;

			case CONSTANT_STRING:
				std::cout << _string << '\n';
				break;

			case CONSTANT_INTEGER:
				std::cout << _integer << '\n';
				break;

			case CONSTANT_FLOAT:
				std::cout << _floating << '\n';
				break;

			case CONSTANT_BOOLEAN:
				std::cout << (_boolean ? "true\n" : "false\n");
				break;
		}
	}

	Constant& Constant::operator=(Constant&& other)
	{
		new(this) auto(other);
		return *this;
	}

	Constant& Constant::operator=(const Constant& other)
	{
		new(this) auto(other);
		return *this;
	}
}
