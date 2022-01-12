#include <warbler/ast/function.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, Expression *inline_body) :
	_name(name),
	_parameters(parameters),
	_return_type(return_type),
	_inline_body(inline_body)
	{}

	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, std::vector<Statement>&& compound_body) :
	_name(name),
	_parameters(parameters),
	_return_type(return_type),
	_compound_body(compound_body)
	{}
	
	Result<Function> Function::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_FUNC)
		{
			errortf(*iter, "expected 'func' but got: %t", &(*iter));
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto name = Identifier::parse(iter);

		if (name.has_error())
			return name.error();

		auto parameters = Parameter::parse_list(iter);

		if (parameters.has_error())
			return parameters.error();
		
		Typename type;

		if (iter->type() == TOKEN_SINGLE_ARROW)
		{
			iter += 1;

			auto res = Typename::parse(iter);
			
			if (res.has_error())
				return res.error();

			type = res.unwrap();
		}
		
		if (iter->type() == TOKEN_LBRACE)
		{
			auto body = Statement::parse_compound(iter);

			if (body.has_error())
				return body.error();

			return Function(name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap());
		}
		else if (iter->type() == TOKEN_DOUBLE_ARROW)
		{
			iter += 1;
			auto body = Expression::parse(iter);

			if (body.has_error())
				return body.error();

			return Function(name.unwrap(), parameters.unwrap(), std::move(type), new Expression(body));
		}
		else
		{
			errortf(*iter, "expected function body but got: %t", &(*iter));
			return ERROR_ARGUMENT;
		}

		if ((error = function_parse_body(function, iter)))
			return error;
	}

	void Function::print_tree(u32 depth) const
	{

	}

	static inline Error function_parse_body(Function *function, TokenIterator& iter)
	{
		Error error;

		switch (iter->type)
		{
			case TOKEN_DOUBLE_ARROW:
				function->is_inline = true;
				
				if ((error = expression_parse(function->inline_body, iter)))
					return error;

				break;

			case TOKEN_LBRACE:
				function->is_inline = false;

				if ((error = compound_statement_parse(function->compound_body, iter)))
					return error;
				break;

			default:
				errortf(*iter, "expected function body but got: %t", iter);
				return ERROR_ARGUMENT;
		}

		return ERROR_NONE;
	}

	static inline Error try_function_parse(Function *function, TokenIterator& iter)
	{
		Error error;

		

		return ERROR_NONE;
	}
}