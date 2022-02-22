#include <warbler/ast/expression/postfix_expression.hpp>

#include <warbler/print.hpp>
#include <warbler/ast/expression/primary_expression.hpp>

// call parse then check for type
// not sure how to do this

namespace warbler::ast
{
	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index) :
	_expression(std::move(expression)),
	_index(std::move(index)),
	_type(POSTFIX_INDEX)
	{}

	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments) :
	_expression(std::move(expression)),
	_arguments(std::move(arguments)),
	_type(POSTFIX_FUNCTION_CALL)
	{}

	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Identifier&& member) :
	_expression(std::move(expression)),
	_member(std::move(member)),
	_type(POSTFIX_MEMBER)
	{}
 
	PostfixExpression::PostfixExpression(PostfixExpression&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				new(&_index) auto(std::move(other._index));
				break;

			case POSTFIX_FUNCTION_CALL:
				new(&_arguments) auto(std::move(other._arguments));
				break;

			case POSTFIX_MEMBER:
				new (&_member) auto(std::move(other._member));				
				break;
		}
	}

	PostfixExpression::~PostfixExpression()
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index.~Ptr();
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments.~vector();
				break;

			case POSTFIX_MEMBER:
				_member.~Identifier();
				break;
		}
	}

	static Result<Array<Ptr<Expression>>> parse_arguments(TokenIterator& iter)
	{
		iter += 1;

		Array<Ptr<Expression>> arguments;

	parse_argument:

		if (iter->type() != TOKEN_RPAREN)
		{
			auto res = Expression::parse(iter);

			if (!res)
				return {};
			
			arguments.emplace_back(res.unwrap());

			if (iter->type() == TOKEN_COMMA)
			{
				iter += 1;
				goto parse_argument;
			}

			if (iter->type() != TOKEN_RPAREN)
			{
				parse_error(iter, "')' after function arguments");
				return {};
			}
		}

		iter += 1;

		return arguments;
	}
	
	Result<Ptr<Expression>> PostfixExpression::parse(TokenIterator& iter)
	{
		auto primary_expression = PrimaryExpression::parse(iter);

		if (!primary_expression)
			return {};

		Ptr<Expression> expression = primary_expression.unwrap();

	parse_postfix:
		switch (iter->type())
		{
			case TOKEN_LBRACK:
			{
				iter += 1;
				auto res = Expression::parse(iter);

				if (!res)
					return {};

				if (iter->type() != TOKEN_RBRACK)
				{
					parse_error(iter, "']' after index operation");
					return {};
				}

				iter += 1;

				expression = new PostfixExpression(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case TOKEN_LPAREN:
			{
				auto res = parse_arguments(iter);

				if (!res)
					return {};

				expression = new PostfixExpression(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case TOKEN_DOT:
			{
				iter += 1;

				auto res = Identifier::parse(iter);

				if (!res)
					return {};
				
				expression = new PostfixExpression { std::move(expression), res.unwrap() };
				goto parse_postfix;
			}
			
			default:
				break;
		}

		return expression;
	}

	bool PostfixExpression::validate(semantics::ModuleContext& module, semantics::FunctionContext& function)
	{
		throw std::runtime_error("PostfixExpression::" + String(__func__) + " is not implemented yet");
	}

	ast::Typename *PostfixExpression::get_type(semantics::ModuleContext& module) const
	{
		throw std::runtime_error("PostfixExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& PostfixExpression::location() const
	{
		throw std::runtime_error("PostfixExpression::" + String(__func__) + " is not implemented yet");
	}

	void PostfixExpression::print_tree(u32 depth) const
	{
		_expression->print_tree(depth);

		switch (_type)
		{
			case POSTFIX_INDEX:
				std::cout << tree_branch(depth) << "[\n";
				_index->print_tree(depth + 1);
				std::cout << tree_branch(depth) << "]\n";
				break;

			case POSTFIX_FUNCTION_CALL:
				std::cout << tree_branch(depth) << "(\n";

				for (const auto& arg : _arguments)
					arg->print_tree(depth + 1);

				std::cout << tree_branch(depth) << ")\n";
				break;

			case POSTFIX_MEMBER:
				std::cout << '.' << _member.text() << '\n';
				break;
		}
	}
}
