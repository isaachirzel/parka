#include <warbler/ast/statement/if_statement.hpp>

#include <warbler/ast/statement/statement.hpp>
#include <warbler/print.hpp>

namespace warbler
{
	IfStatement::IfStatement(Expression&& condition, std::vector<Statement>&& then_body) :
	_condition(condition),
	_then_body(then_body),
	_type(IF_THEN)
	{}

	IfStatement::IfStatement(Expression&& condition, std::vector<Statement>&& then_body, std::vector<Statement>&& else_body) :
	_condition(condition),
	_then_body(then_body),
	_else_body(else_body),
	_type(IF_THEN_ELSE)
	{}

	IfStatement::IfStatement(Expression&& condition, std::vector<Statement>&& then_body, IfStatement *else_if) :
	_condition(condition),
	_then_body(then_body),
	_else_if(else_if),
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

	IfStatement::IfStatement(const IfStatement& other) :
	_condition(other._condition),
	_then_body(other._then_body),
	_type(other._type)
	{
		switch (_type)
		{
			case IF_THEN:
				break;

			case IF_THEN_ELSE:
				new(&_else_body) auto(other._else_body);
				break;

			case IF_THEN_ELSE_IF:
				_else_if = new IfStatement(*other._else_if);
				break;
		}
	}

	IfStatement::~IfStatement()
	{
		if (_type == IF_THEN_ELSE)
		{
			_else_body.~vector();
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

		if (condition.has_error())
			return condition.error();

		auto then_body = Statement::parse_compound(iter);

		if (then_body.has_error())
			return then_body.error();

		if (iter->type() == TOKEN_ELSE)
		{
			iter += 1;

			if (iter->type() == TOKEN_IF)
			{
				auto else_if = IfStatement::parse(iter);

				if (else_if.has_error())
					return else_if.error();

				return IfStatement(condition.unwrap(), then_body.unwrap(), new IfStatement(else_if.unwrap()));
			}
			else
			{
				auto else_body = Statement::parse_compound(iter);

				if (else_body.has_error())
					return else_body.error();

				return IfStatement(condition.unwrap(), then_body.unwrap(), else_body.unwrap());
			}
		}
		
		return IfStatement(condition.unwrap(), then_body.unwrap());
	}

	void IfStatement::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << "if\n";
		_condition.print_tree(depth + 1);
		std::cout << tree_branch(depth + 1) << "{\n";

		for (const auto& statement : _then_body)
			statement.print_tree(depth + 2);

		std::cout << tree_branch(depth + 1) << "}\n";

		if (_type == IF_THEN_ELSE)
		{
			std::cout << tree_branch(depth + 1) << "else\n";
			std::cout << tree_branch(depth + 1) << "{\n";

			for (const auto& statement : _else_body)
				statement.print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << "}\n";
		}
		else if (_type == IF_THEN_ELSE_IF)
		{
			std::cout << tree_branch(depth + 1) << "else\n";

			_else_if->print_tree(depth + 2);
		}
	}

	IfStatement IfStatement::operator=(IfStatement&& other)
	{
		new (this) auto(other);
		return *this;
	}

	IfStatement IfStatement::operator=(const IfStatement& other)
	{
		new (this) auto(other);
		return *this;
	}
}
