#include <warbler/syntax/function.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Function::Function(Identifier&& name, Array<Declaration>&& parameters, Type&& return_type, BlockStatement&& body) :
	_name(std::move(name)),
	_parameters(std::move(parameters)),
	_return_type(std::move(return_type)),
	_body(std::move(body))
	{}

	static Result<Array<Declaration>> parse_parameters(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TOKEN_LPAREN)
		{
			print_parse_error(iter, "'(' after function name");
			return {};
		}

		iter += 1;

		Array<Declaration> parameters;

		if (iter->type() != lexicon::TOKEN_RPAREN)
		{
			while (true)
			{
				auto res = Declaration::parse_parameter(iter);

				if (!res)
					return {};

				parameters.emplace_back(res.unwrap());

				if (iter->type() != lexicon::TOKEN_COMMA)
					break;

				iter += 1;
			}

			if (iter->type() != lexicon::TOKEN_RPAREN)
			{
				print_parse_error(iter, "')' after function parameters");
				return {};
			}
		}

		iter += 1;

		return parameters;
	}

	Result<Function> Function::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TOKEN_FUNC)
		{
			print_parse_error(iter, "'function'");
			return {};
		}

		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		auto parameters = parse_parameters(iter);

		if (!parameters)
			return {};
		
		auto type = Type();

		if (iter->type() == lexicon::TOKEN_COLON)
		{
			iter += 1;

			auto res = Type::parse(iter);
			
			if (!res)
				return {};

			type = res.unwrap();
		}

		if (iter->type() != lexicon::TOKEN_LBRACE)
		{
			print_parse_error(iter, "function body starting with '{'");
			return {};
		}
		
		auto body = BlockStatement::parse(iter);

		if (!body)
			return {};

		return Function(name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap());
	}

	bool Function::validate(semantics::ModuleContext& mod_ctx)
	{
		_context.blocks.push_back(&_body.context());

		for (auto& parameter : _parameters)
		{
			if (!parameter.validate_parameter(mod_ctx, _context))
				return false;
		}

		return _return_type.validate(mod_ctx) && _body.validate(mod_ctx, _context);
	}

	void Function::print_tree(u32 depth) const 
	{
		std::cout << tree_branch(depth) << "function " << _name.text() << '\n';
		std::cout << tree_branch(depth + 1) << "(\n";

		for (const auto& parameter : _parameters)
			parameter.print_tree(depth + 2);

		std::cout << tree_branch(depth + 1) << ")\n";
		std::cout << tree_branch(depth + 1) << ": " << _return_type.text() << '\n';
		
		_body.print_tree(depth + 1);
	}
}