#include <warbler/syntax/statement/if_statement.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_type(IfType::Then)
	{}

	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body, BlockStatement&& else_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_body(std::move(else_body)),
	_type(IfType::ThenElse)
	{}

	IfStatement::IfStatement(Ptr<Expression>&& condition, BlockStatement&& then_body, IfStatement *else_if) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_if(std::move(else_if)),
	_type(IfType::ThenElseIf)
	{}

	IfStatement::IfStatement(IfStatement&& other) :
	_condition(std::move(other._condition)),
	_then_body(std::move(other._then_body)),
	_type(other._type)
	{
		switch (_type)
		{
			case IfType::Then:
				break;

			case IfType::ThenElse:
				new(&_else_body) auto(std::move(other._else_body));
				break;

			case IfType::ThenElseIf:
				_else_if = other._else_if;
				other._else_if = nullptr;
				break;
		}
	}

	IfStatement::~IfStatement()
	{
		if (_type == IfType::ThenElse)
		{
			_else_body.~BlockStatement();
		}
		else if (_type == IfType::ThenElseIf)
		{
			delete _else_if;
		}
	}

	Result<IfStatement> IfStatement::parse(lexicon::TokenIterator& iter)
	{
		iter += 1;
		
		auto condition = Expression::parse(iter);

		if (!condition)
			return {};

		auto then_body = BlockStatement::parse(iter);

		if (!then_body)
			return {};

		if (iter->type() == lexicon::TokenType::KeywordElse)
		{
			iter += 1;

			if (iter->type() == lexicon::TokenType::KeywordIf)
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

	// bool IfStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	throw std::runtime_error("IfStatement::validate is not implemented yet");
	// }

	void IfStatement::print_tree(u32 depth) const
	{
		print_branch(depth, "if");
		_condition->print_tree(depth + 1);
		print_branch(depth, "then");
		_then_body.print_tree(depth + 1);

		if (_type == IfType::Then)
			return;

		print_branch(depth, "else");

		if (_type == IfType::ThenElse)
		{
			_else_body.print_tree(depth + 1);
		}
		else if (_type == IfType::ThenElseIf)
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
