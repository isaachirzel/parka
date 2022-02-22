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

	static Constant parse_character(TokenIterator& iter)
	{
		const auto& loc = iter->location();
		u32 character = (u32)loc[0];

		iter += 1;

		return Constant(character);
	}

	static f64 string_to_f64(const Token& token)
	{
		f64 out = 0.0;

		const auto& location = token.location();
		const char *text = location.pos_ptr();
		usize length = location.length();

		for (size_t i = 0; i < length; ++i)
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

				while (i < length)
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

	static i64 string_to_i64(const Token& token)
	{
		i64 out = 0;
		const auto& location = token.location();
		const char *text = location.pos_ptr();
		usize length = location.length();

		for (size_t i = 0; i < length; ++i)
			out = out * 10 + (text[i] - '0');

		return out;
	}

	static Constant parse_integer_literal(TokenIterator& iter, bool is_negative)
	{
		i64 value = string_to_i64(*iter);

		if (is_negative)
			value = -value;

		iter += 1;

		return Constant(value);
	}

	static Constant parse_float_literal(TokenIterator& iter, bool is_negative)
	{
		f64 value = string_to_f64(*iter);

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
				error_out(iter) << "expected number literal but got '" << *iter << '\'';
				error_highlight(iter);
				return {};
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
				break;

			case TOKEN_BINARY_LITERAL:
				break;

			case TOKEN_OCTAL_LITERAL:
				break;

			case TOKEN_CHAR_LITERAL:
				return parse_character(iter);

			case TOKEN_STRING_LITERAL:
			{
				const auto& location = iter->location();
				String string(location.pos_ptr(), location.length());

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

		parse_error(iter, "constant");

		return {};
	}

	bool Constant::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		#pragma message("Implement byte counting for each data type")
		#pragma message("Implemented Constant type validation")
		//throw std::runtime_error("Constant::validate is not implemented yet");
		return true;
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

	Typename *Constant::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("Constant::" + String(__func__) + " is not implemented yet");
	}

	const Location& Constant::location() const
	{
		throw std::runtime_error("Constant::" + String(__func__) + " is not implemented yet");
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
