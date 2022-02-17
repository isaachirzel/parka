#include <warbler/ast/expression/postfix_expression.hpp>


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

	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Name&& member) :
	_expression(std::move(expression)),
	_member(std::move(member)),
	_type(POSTFIX_MEMBER)
	{}
	
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

					expression = new PostfixExpression { std::move(expression), res.unwrap() };
					goto parse_postfix;
				}

				case TOKEN_LPAREN:
					auto res = Argument::parse_list(iter);

					if (!res)
						return {};

					expression = new PostfixExpression { std::move(expression), res.unwrap() };
					goto parse_postfix;

				case TOKEN_DOT:
					iter += 1;

					auto res = Name::parse(iter);

					if (!res)
						return {};
					
					expression = new PostfixExpression { std::move(expression), res.unwrap() };
					goto parse_postfix;

				default:
					break;
			}
		}
	}
}
