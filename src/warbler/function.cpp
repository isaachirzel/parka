#include <warbler/ast/function.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, Expression&& inline_body) :
	_name(name),
	_parameters(parameters),
	_return_type(return_type),
	_inline_body(inline_body),
	_is_inline(true)
	{}

	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, std::vector<Statement>&& compound_body) :
	_name(name),
	_parameters(parameters),
	_return_type(return_type),
	_compound_body(compound_body),
	_is_inline(false)
	{}
	
	Function::Function(Function&& other) :
	_name(std::move(other._name)),
	_parameters(std::move(other._parameters)),
	_return_type(std::move(other._return_type)),
	_is_inline(other._is_inline)
	{
		if (_is_inline)
		{
			new(&_inline_body) auto(std::move(other._inline_body));
		}
		else
		{
			new(&_compound_body) auto(std::move(other._compound_body));
		}
	}

	Function::Function(const Function& other) :
	_name(other._name),
	_parameters(other._parameters),
	_return_type(other._return_type),
	_is_inline(other._is_inline)
	{
		if (_is_inline)
		{
			new(&_inline_body) auto(other._inline_body);
		}
		else
		{
			new(&_compound_body) auto(other._compound_body);
		}
	}

	Function::~Function()
	{
		if (_is_inline)
		{
			_inline_body.~ConditionalExpression();
		}
		else
		{
			_compound_body.~vector();
		}
	}

	Result<Function> Function::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_FUNC)
		{
			error_out(iter) << "expected 'func' but got: " << *iter << std::endl;
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
		
			return Function(name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap());
		}
		else
		{
			error_out(iter) << "expected function body but got '" << *iter << '\'' << token_error(iter) << std::endl;
			return ERROR_ARGUMENT;
		}
	}

	void Function::print_tree(u32 depth) const 
	{
		_name.print_tree(depth);

		std::cout << tree_branch(depth + 1) << "(\n";

		for (const auto& parameter : _parameters)
			parameter.print_tree(depth + 2);

		std::cout << tree_branch(depth + 1) << ")\n";

		_return_type.print_tree(depth + 1);

		if (_is_inline)
		{
			_inline_body.print_tree(depth + 1);
		}
		else
		{
			std::cout << tree_branch(depth + 1) << "{\n";

			for (const auto& statement : _compound_body)
				statement.print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << "}\n";
		}
	}

	Function& Function::operator=(Function&& other)
	{
		new(this) auto(other);
		return *this;
	}

	Function& Function::operator=(const Function& other)
	{
		new(this) auto(other);
		return *this;
	}
}