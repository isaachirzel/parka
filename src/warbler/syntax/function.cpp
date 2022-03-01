#include <warbler/syntax/function.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Function::Function(Identifier&& name, Array<Declaration>&& parameters, Optional<Type>&& return_type, BlockStatement&& body) :
	_name(std::move(name)),
	_parameters(std::move(parameters)),
	_return_type(std::move(return_type)),
	_body(std::move(body))
	{}

	static Result<Array<Declaration>> parse_parameters(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::LeftParenthesis)
		{
			print_parse_error(token, "'(' after function name");
			return {};
		}

		Array<Declaration> parameters;

		if (token.next().type() != lexicon::TokenType::RightParenthesis)
		{
			while (true)
			{
				auto res = Declaration::parse_parameter(token);

				if (!res)
					return {};

				parameters.emplace_back(res.unwrap());

				if (token.type() != lexicon::TokenType::Comma)
					break;

				token.next();
			}

			if (token.type() != lexicon::TokenType::RightParenthesis)
			{
				print_parse_error(token, "')' after function parameters");
				return {};
			}
		}

		token.next();

		return parameters;
	}

	Result<Function> Function::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::KeywordFunction)
		{
			print_parse_error(token, "'function'");
			return {};
		}

		auto name = Identifier::parse(token.next());

		if (!name)
			return {};

		auto parameters = parse_parameters(token);

		if (!parameters)
			return {};
		
		Optional<Type> type;

		if (token.type() == lexicon::TokenType::Colon)
		{
			auto res = Type::parse(token.next());
			
			if (!res)
				return {};

			type = res.unwrap();
		}

		if (token.type() != lexicon::TokenType::LeftBrace)
		{
			print_parse_error(token, "function body starting with '{'");
			return {};
		}
		
		auto body = BlockStatement::parse(token.next());

		if (!body)
			return {};

		return Function(name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap());
	}

	// bool Function::validate(semantics::ModuleContext& mod_ctx)
	// {
	// 	_context.blocks.push_back(&_body.context());

	// 	for (auto& parameter : _parameters)
	// 	{
	// 		if (!parameter.validate_parameter(mod_ctx, _context))
	// 			return false;
	// 	}

	// 	return _return_type.validate(mod_ctx) && _body.validate(mod_ctx, _context);
	// }

	void Function::print_tree(u32 depth) const 
	{
		print_branch(depth, "function " + _name.token().text());
		print_branch(depth + 1, "(");

		for (const auto& parameter : _parameters)
			parameter.print_tree(depth + 2);

		print_branch(depth + 1, ")");
		print_branch(depth + 1, ": " + _return_type ? _return_type->base_type().text() : "void");

		_body.print_tree(depth + 1);
	}
}