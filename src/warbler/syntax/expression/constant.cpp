#include <warbler/syntax/expression/constant.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstring>

namespace warbler::syntax
{
	Constant::Constant(const source::Location& location, ConstantType type) :
	_location(location),
	_type(type)
	{}

	// Constant::Constant(const source::Location& location, i64 integer) :
	// _location(location),
	// _integer(integer),
	// _constant_type(ConstantINTEGER)
	// {}

	// Constant::Constant(const source::Location& location, f64 floating) :
	// _location(location),
	// _floating(floating),
	// _constant_type(ConstantFLOAT)
	// {}

	// Constant::Constant(const source::Location& location, u32 character) :
	// _location(location),
	// _character(character),
	// _constant_type(ConstantCHARACTER)
	// {}

	// Constant::Constant(const source::Location& location, bool boolean) :
	// _location(location),
	// _boolean(boolean),
	// _constant_type(ConstantBOOLEAN)
	// {}

	// Constant::Constant(Constant&& other) :
	// _location(other._location),
	// _constant_type(other._constant_type)
	// {
	// 	switch (_constant_type)
	// 	{
	// 		case ConstantCHARACTER:
	// 			_character = other._character;
	// 			break;

	// 		case ConstantSTRING:
	// 			new(&_string) auto(std::move(other._string));
	// 			break;

	// 		case ConstantINTEGER:
	// 			_integer = other._integer;
	// 			break;

	// 		case ConstantFLOAT:
	// 			_floating = other._floating;
	// 			break;

	// 		case ConstantBOOLEAN:
	// 			_boolean = other._boolean;
	// 			break;
	// 	}

	// 	other._constant_type = ConstantINTEGER;
	// }

	// Constant::~Constant()
	// {
	// 	if (_constant_type == ConstantSTRING)
	// 		_string.~basic_string();
	// }

	// static Constant parse_character(lexicon::TokenIterator& iter)
	// {
	// 	const auto& location = iter->location();
	// 	auto text = location.text();
	// 	u32 character = (u32)text[0];

	// 	iter += 1;

	// 	return Constant(location, character);
	// }

	// static f64 string_to_f64(const lexicon::Token& token)
	// {
	// 	f64 out = 0.0;

	// 	const auto& location = token.location();
	// 	const char *text = location.pos_ptr();
	// 	usize length = location.length();

	// 	for (size_t i = 0; i < length; ++i)
	// 	{
	// 		if (text[i] != '.')
	// 		{
	// 			out = out * 10.0 + (text[i] - '0');
	// 		}
	// 		else
	// 		{
	// 			i += 1;

	// 			f64 decimal = 0.0;
	// 			f64 place = 1.0;

	// 			while (i < length)
	// 			{
	// 				decimal = decimal * 10.0 + (text[i] - '0');
	// 				place *= 10.0;
	// 				++i;
	// 			}
				
	// 			out += (decimal / place);
	// 			break;
	// 		}
	// 	}
		
	// 	return out;
	// }

	// static i64 string_to_i64(const lexicon::Token& token)
	// {
	// 	i64 out = 0;
	// 	const auto& location = token.location();
	// 	const char *text = location.pos_ptr();
	// 	usize length = location.length();

	// 	for (size_t i = 0; i < length; ++i)
	// 		out = out * 10 + (text[i] - '0');

	// 	return out;
	// }

	// static Constant parse_integer_literal(lexicon::TokenIterator& iter, bool is_negative)
	// {
	// 	i64 value = string_to_i64(*iter);

	// 	if (is_negative)
	// 		value = -value;

	// 	const auto& location = iter->location();

	// 	iter += 1;

	// 	return Constant(location, value);
	// }

	// static Constant parse_float_literal(lexicon::TokenIterator& iter, bool is_negative)
	// {
	// 	f64 value = string_to_f64(*iter);

	// 	if (is_negative)
	// 		value = -value;

	// 	const auto& location = iter->location();

	// 	iter += 1;

	// 	return Constant(location, value);
	// }

	static Result<Constant> parse_number(lexicon::TokenIterator& iter, bool is_negative)
	{
		switch (iter->type())
		{
			case lexicon::TokenType::IntegerLiteral:
				return Constant(iter->location(), ConstantType::Integer);

			case lexicon::TokenType::FloatLiteral:
				return Constant(iter->location(), ConstantType::Float);

			default:
				print_parse_error(iter, "number literal");
				return {};
		}
	}

	Result<Constant> Constant::parse(lexicon::TokenIterator& iter)
	{
		switch (iter->type())
		{
			case lexicon::TokenType::CharLiteral:
				return Constant(iter->location(), ConstantType::Character);

			case lexicon::TokenType::StringLiteral:
				return Constant(iter->location(), ConstantType::String);

			case lexicon::TokenType::IntegerLiteral:
				return Constant(iter->location(), ConstantType::Integer);

			case lexicon::TokenType::BinaryLiteral:
				return Constant(iter->location(), ConstantType::Integer);

			case lexicon::TokenType::HexadecimalLiteral:
				return Constant(iter->location(), ConstantType::Integer);

			case lexicon::TokenType::OctalLiteral:
				return Constant(iter->location(), ConstantType::Octal);

			case lexicon::TokenType::FloatLiteral:
				return Constant(iter->location(), ConstantType::Float);

			case lexicon::TokenType::KeywordTrue:
				return Constant(iter->location(), ConstantType::BooleanTrue);

			case lexicon::TokenType::KeywordFalse:
				return Constant(iter->location(), ConstantType::BooleanFalse);

			default:
				print_parse_error(iter, "constant");
				return {};
		}
	}

	// bool Constant::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	#pragma message("Implement byte counting for each data type")

	// 	const char *type_base_name;

	// 	switch (_constant_type)
	// 	{
	// 		case ConstantCHARACTER:
	// 			type_base_name = "char";
	// 			break;

	// 		case ConstantSTRING:
	// 			type_base_name = "str";
	// 			break;

	// 		case ConstantINTEGER:
	// 			type_base_name = "i64";
	// 			break;

	// 		case ConstantFLOAT:
	// 			type_base_name = "f64";
	// 			break;

	// 		case ConstantBOOLEAN:
	// 			type_base_name = "bool";
	// 			break;
	// 	}

	// 	auto *definition = mod_ctx.get_type(type_base_name);

	// 	assert(definition != nullptr);

	// 	_type = Type(type_base_name, definition);

	// 	return true;
	// }

	void Constant::print_tree(u32 depth) const
	{
		print_branch(depth, _location.text());
	}
}
