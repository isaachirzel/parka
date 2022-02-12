#include <warbler/ast/function.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/semantics/symbol.hpp>

namespace warbler::ast
{
	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, Ptr<Expression>&& inline_body) :
	_name(std::move(name)),
	_parameters(std::move(parameters)),
	_return_type(std::move(return_type)),
	_inline_body(std::move(inline_body)),
	_is_inline(true)
	{}

	Function::Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, CompoundStatement&& compound_body) :
	_name(std::move(name)),
	_parameters(std::move(parameters)),
	_return_type(std::move(return_type)),
	_compound_body(std::move(compound_body)),
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

	Function::~Function()
	{
		if (_is_inline)
		{
			_inline_body.~Ptr();
		}
		else
		{
			_compound_body.~CompoundStatement();
		}
	}

	Result<Function> Function::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_FUNC)
		{
			error_out(iter) << "expected 'func' but got: " << *iter << std::endl;
			return {};
		}

		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		auto parameters = Parameter::parse_list(iter);

		if (!parameters)
			return {};
		
		Typename type(iter->location());

		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Typename::parse(iter);
			
			if (!res)
				return {};

			type = res.unwrap();
		}
		
		if (iter->type() == TOKEN_LBRACE)
		{
			auto body = CompoundStatement::parse(iter);

			if (!body)
				return {};

			return Function(name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap());
		}
		else if (iter->type() == TOKEN_DOUBLE_ARROW)
		{
			iter += 1;
			auto body = Expression::parse(iter);

			if (!body)
				return {};
		
			return Function { name.unwrap(), parameters.unwrap(), std::move(type), body.unwrap() };
		}
		else
		{
			parse_error(iter, "fucntion body");
			return {};
		}
	}

	void Function::print_tree(u32 depth) const 
	{
		std::cout << tree_branch(depth) << "func\n";
		_name.print_tree(depth + 1);

		std::cout << tree_branch(depth + 2) << "(\n";

		for (const auto& parameter : _parameters)
			parameter.print_tree(depth + 3);

		std::cout << tree_branch(depth + 2) << ")\n";
		std::cout << tree_branch(depth + 2) << ":\n";
		
		_return_type.print_tree(depth + 3);

		if (_is_inline)
		{
			_inline_body->print_tree(depth + 1);
		}
		else
		{
			_compound_body.print_tree(depth + 1);
		}
	}

	bool Function::validate(semantics::ModuleContext& context)
	{
		Set<String> parameter_names;

		for (auto& parameter : _parameters)
		{
			const auto& name = parameter.name().text();

			if (parameter_names.find(name) != parameter_names.end())
			{
				error_out(parameter.name().location()) << "function " << context.module_name << "::" << _name.text() << "(...) already contains parameter '" << name << '\'';
				error_highlight(parameter.name().location());

				return false;
			}

			parameter_names.insert(name);

			if (!parameter.validate(context))
				return false;
		}

		// auto status = _return_type.validate();

		// if (!status)
		// 	return status;

		// if (_is_inline)
		// {
 
		// }
		// else
		// {
		// 	for (
		// }

		return true;
	}

	Function& Function::operator=(Function&& other)
	{
		new(this) auto(std::move(other));
		return *this;
	}
}