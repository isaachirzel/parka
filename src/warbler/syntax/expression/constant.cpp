#include <warbler/syntax/expression/constant.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstring>

namespace warbler::syntax
{
	Constant::Constant(const source::Location& location, String&& string) :
	_location(location),
	_string(string),
	_constant_type(CONSTANT_STRING)
	{}

	Constant::Constant(const source::Location& location, i64 integer) :
	_location(location),
	_integer(integer),
	_constant_type(CONSTANT_INTEGER)
	{}

	Constant::Constant(const source::Location& location, f64 floating) :
	_location(location),
	_floating(floating),
	_constant_type(CONSTANT_FLOAT)
	{}

	Constant::Constant(const source::Location& location, u32 character) :
	_location(location),
	_character(character),
	_constant_type(CONSTANT_CHARACTER)
	{}

	Constant::Constant(const source::Location& location, bool boolean) :
	_location(location),
	_boolean(boolean),
	_constant_type(CONSTANT_BOOLEAN)
	{}

	Constant::Constant(Constant&& other) :
	_location(other._location),
	_constant_type(other._constant_type)
	{
		switch (_constant_type)
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

		other._constant_type = CONSTANT_INTEGER;
	}

	Constant::~Constant()
	{
		if (_constant_type == CONSTANT_STRING)
			_string.~basic_string();
	}

	static Constant parse_character(lexicon::TokenIterator& iter)
	{
		const auto& location = iter->location();
		u32 character = (u32)location[0];

		iter += 1;

		return Constant(location, character);
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

	static Constant parse_integer_literal(lexicon::TokenIterator& iter, bool is_negative)
	{
		i64 value = string_to_i64(*iter);

		if (is_negative)
			value = -value;

		const auto& location = iter->location();

		iter += 1;

		return Constant(location, value);
	}

	static Constant parse_float_literal(lexicon::TokenIterator& iter, bool is_negative)
	{
		f64 value = string_to_f64(*iter);

		if (is_negative)
			value = -value;

		const auto& location = iter->location();

		iter += 1;

		return Constant(location, value);
	}

	static Result<Constant> parse_number(lexicon::TokenIterator& iter, bool is_negative)
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

	Result<Constant> Constant::parse(lexicon::TokenIterator& iter)
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

				return Constant(location, std::move(string));
			}

			case TOKEN_TRUE:
			{
				const auto& location = iter->location();
				iter += 1;
				return Constant(location, true);
			}

			case TOKEN_FALSE:
			{
				const auto& location = iter->location();

				iter += 1;
				return Constant(location, false);
			}

			default:
				break;
		}

		print_parse_error(iter, "constant");

		return {};
	}

	bool Constant::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		std::cout << "Constant::" << __func__ << std::endl;

		#pragma message("Implement byte counting for each data type")

		const char *type_base_name;

		switch (_constant_type)
		{
			case CONSTANT_CHARACTER:
				type_base_name = "char";
				break;

			case CONSTANT_STRING:
				type_base_name = "str";
				break;

			case CONSTANT_INTEGER:
				type_base_name = "i64";
				break;

			case CONSTANT_FLOAT:
				type_base_name = "f64";
				break;

			case CONSTANT_BOOLEAN:
				type_base_name = "bool";
				break;
		}

		auto *definition = mod_ctx.get_type(type_base_name);

		assert(definition != nullptr);

		_type = Type(type_base_name, definition);

		return true;
	}

	void Constant::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		switch (_constant_type)
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
		new(this) auto(std::move(other));
		return *this;
	}
}
