#include <warbler/syntax/expression/constant.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstring>

namespace warbler::syntax
{
	Constant::Constant(const lexicon::Token& token, ConstantType type) :
	_token(token),
	_type(type)
	{}

	// Constant::Constant(const lexicon::Token& token, i64 integer) :
	// _token(token),
	// _integer(integer),
	// _constant_type(ConstantINTEGER)
	// {}

	// Constant::Constant(const lexicon::Token& token, f64 floating) :
	// _token(token),
	// _floating(floating),
	// _constant_type(ConstantFLOAT)
	// {}

	// Constant::Constant(const lexicon::Token& token, u32 character) :
	// _token(token),
	// _character(character),
	// _constant_type(ConstantCHARACTER)
	// {}

	// Constant::Constant(const lexicon::Token& token, bool boolean) :
	// _token(token),
	// _boolean(boolean),
	// _constant_type(ConstantBOOLEAN)
	// {}

	// Constant::Constant(Constant&& other) :
	// _token(other._token),
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

	// static Constant parse_character(const lexicon::Token& token)
	// {
	// 	const auto& token = token;
	// 	auto text = token.text();
	// 	u32 character = (u32)text[0];

	// 	token.next();

	// 	return Constant(token, character);
	// }

	// static f64 string_to_f64(const lexicon::Token& token)
	// {
	// 	f64 out = 0.0;

	// 	const auto& token = token.token();
	// 	const char *text = token.pos_ptr();
	// 	usize length = token.length();

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
	// 	const auto& token = token.token();
	// 	const char *text = token.pos_ptr();
	// 	usize length = token.length();

	// 	for (size_t i = 0; i < length; ++i)
	// 		out = out * 10 + (text[i] - '0');

	// 	return out;
	// }

	// static Constant parse_integer_literal(const lexicon::Token& token, bool is_negative)
	// {
	// 	i64 value = string_to_i64(*iter);

	// 	if (is_negative)
	// 		value = -value;

	// 	const auto& token = token;

	// 	token.next();

	// 	return Constant(token, value);
	// }

	// static Constant parse_float_literal(const lexicon::Token& token, bool is_negative)
	// {
	// 	f64 value = string_to_f64(*iter);

	// 	if (is_negative)
	// 		value = -value;

	// 	const auto& token = token;

	// 	token.next();

	// 	return Constant(token, value);
	// }

	static Result<Constant> parse_number(const lexicon::Token& token, bool is_negative)
	{
		switch (token.type())
		{
			case lexicon::TokenType::IntegerLiteral:
				return Constant(token, ConstantType::Integer);

			case lexicon::TokenType::FloatLiteral:
				return Constant(token, ConstantType::Float);

			default:
				print_parse_error(token, "number literal");
				return {};
		}
	}

	Result<Constant> Constant::parse(lexicon::Token& token)
	{
		switch (token.type())
		{
			case lexicon::TokenType::CharLiteral:
				return Constant(token, ConstantType::Character);

			case lexicon::TokenType::StringLiteral:
				return Constant(token, ConstantType::String);

			case lexicon::TokenType::IntegerLiteral:
				return Constant(token, ConstantType::Integer);

			case lexicon::TokenType::BinaryLiteral:
				return Constant(token, ConstantType::Integer);

			case lexicon::TokenType::HexadecimalLiteral:
				return Constant(token, ConstantType::Integer);

			case lexicon::TokenType::OctalLiteral:
				return Constant(token, ConstantType::Octal);

			case lexicon::TokenType::FloatLiteral:
				return Constant(token, ConstantType::Float);

			case lexicon::TokenType::KeywordTrue:
				return Constant(token, ConstantType::BooleanTrue);

			case lexicon::TokenType::KeywordFalse:
				return Constant(token, ConstantType::BooleanFalse);

			default:
				print_parse_error(token, "constant");
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
		print_branch(depth, _token.text());
	}
}
