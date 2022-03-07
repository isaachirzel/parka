#include <warbler/syntax/function/parameter.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Parameter::Parameter(bool is_mutable, Identifier&& identifier, Type&& type) :
	_is_mutable(is_mutable),
	_identifier(identifier),
	_type(type)
	{}

	Result<Parameter> Parameter::parse(lexicon::Token& token)
	{
		bool is_mutable = false;

		if (token.type() == lexicon::TokenType::KeywordMut)
		{
			is_mutable = true;
			token.next();
		}

		auto name = Identifier::parse(token);
		
		if (!name)
			return {};

		if (token.type() != lexicon::TokenType::Colon)
		{
			print_parse_error(token, ":", "Parameters require a valid type");
			return {};
		}

		auto type = Type::parse(token.next());

		if (!type)
			return {};

		return Parameter(is_mutable, name.unwrap(), type.unwrap());
	}

	Result<Array<Parameter>> Parameter::parse_list(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::LeftParenthesis)
		{
			print_parse_error(token, "'(' after function name");
			return {};
		}

		Array<Parameter> parameters;

		if (token.next().type() != lexicon::TokenType::RightParenthesis)
		{
			while (true)
			{
				auto res = Parameter::parse(token);

				if (!res)
					return {};

				parameters.emplace_back(res.unwrap());

				if (token.type() != lexicon::TokenType::Comma)
					break;

				token.next();
			}

			if (token.type() != lexicon::TokenType::RightParenthesis)
			{
				print_parse_error(token, "')'", "Invalid tokens in parameter list");
				return {};
			}

			return parameters;
		}

		token.next();

		return parameters;
	}
}
