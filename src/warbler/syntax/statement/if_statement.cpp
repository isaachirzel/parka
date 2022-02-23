#include <warbler/syntax//statement/if_statement.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_type(IF_THEN)
	{}

	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body, BlockStatement&& else_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_body(std::move(else_body)),
	_type(IF_THEN_ELSE)
	{}

	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body, IfStatement *else_if) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_if(std::move(else_if)),
	_type(IF_THEN_ELSE_IF)
	{}

	IfStatement::IfStatement(IfStatement&& other) :
	_condition(std::move(other._condition)),
	_then_body(std::move(other._then_body)),
	_type(other._type)
	{
		switch (_type)
		{
			case IF_THEN:
				break;

			case IF_THEN_ELSE:
				new(&_else_body) auto(std::move(other._else_body));
				break;

			case IF_THEN_ELSE_IF:
				_else_if = other._else_if;
				other._else_if = nullptr;
				break;
		}
	}

	IfStatement::~IfStatement()
	{
		if (_type == IF_THEN_ELSE)
		{
			_else_body.~BlockStatement();
		}
		else if (_type == IF_THEN_ELSE_IF)
		{
			delete _else_if;
		}
	}

	Result<IfStatement> IfStatement::parse(TokenIterator& iter)
	{
		iter += 1;
		
		auto condition = Expression::parse(iter);

		if (!condition)
			return {};

		auto then_body = BlockStatement::parse(iter);

		if (!then_body)
			return {};

		if (iter->type() == TOKEN_ELSE)
		{
			iter += 1;

			if (iter->type() == TOKEN_IF)
			{
				auto else_if = IfStatement::parse(iter);

				if (!else_if)
					return {};

				return IfStatement { condition.unwrap(), then_body.unwrap(), new IfStatement(else_if.unwrap()) };
			}
			else
			{
				auto else_body = BlockStatement::parse(iter);

				if (!else_body)
					return {};

				return IfStatement { condition.unwrap(), then_body.unwrap(), else_body.unwrap() };
			}
		}
		
		return IfStatement(condition.unwrap(), then_body.unwrap());
	}

	bool IfStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		throw std::runtime_error("IfStatement::validate is not implemented yet");
	}

	void IfStatement::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << "if\n";
		_condition->print_tree(depth + 1);
		_then_body.print_tree(depth + 1);

		if (_type == IF_THEN)
			return;

		std::cout << tree_branch(depth + 1) << "else\n";

		if (_type == IF_THEN_ELSE)
		{
			_else_body.print_tree(depth + 1);
		}
		else if (_type == IF_THEN_ELSE_IF)
		{
			_else_if->print_tree(depth + 2);
		}
	}

	IfStatement& IfStatement::operator=(IfStatement&& other)
	{
		new (this) auto(std::move(other));
		return *this;
	}
}
