#include <warbler/ast/expression/primary_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>

// standard headers
#include <cassert>
#include <cstdlib>

namespace warbler
{
	PrimaryExpression::PrimaryExpression(std::vector<Prefix>&& prefixes,
		std::vector<Postfix>&& postfixes, Identifier&& identifier) :
	_prefixes(prefixes),
	_postfixes(postfixes),
	_identifier(identifier),
	_type(PRIMARY_IDENTIFIER)
	{}

	PrimaryExpression::PrimaryExpression(std::vector<Prefix>&& prefixes,
		std::vector<Postfix>&& postfixes, Constant&& constant) :
	_prefixes(prefixes),
	_postfixes(postfixes),
	_constant(constant),
	_type(PRIMARY_CONSTANT)
	{}

	PrimaryExpression::PrimaryExpression(std::vector<Prefix>&& prefixes,
		std::vector<Postfix>&& postfixes, Expression *expression) :
	_prefixes(prefixes),
	_postfixes(postfixes),
	_expression(expression),
	_type(PRIMARY_EXPRESSION)
	{}

	PrimaryExpression::PrimaryExpression(PrimaryExpression&& other) :
	_prefixes(std::move(other._prefixes)),
	_postfixes(std::move(other._postfixes)),
	_type(other._type)
	{
		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				_identifier = std::move(other._identifier);
				break;

			case PRIMARY_CONSTANT:
				_constant = std::move(other._constant);
				break;

			case PRIMARY_EXPRESSION:
				_expression = other._expression;
				break;
		}

		other._expression = nullptr;
		other._type = PRIMARY_EXPRESSION;
	}

	PrimaryExpression::PrimaryExpression(const PrimaryExpression& other) :
	_prefixes(other._prefixes),
	_postfixes(other._postfixes),
	_type(other._type)
	{}
	
	PrimaryExpression::~PrimaryExpression()
	{
		if (_type == PRIMARY_IDENTIFIER)
		{
			_identifier.~Identifier();
		}
		else if (_type == PRIMARY_CONSTANT)
		{
			_constant.~Constant();
		}
		else // PRIMARY_EXPRESSION
		{
			delete _expression;
		}
	}

	Result<PrimaryExpression> PrimaryExpression::parse(TokenIterator& iter)
	{
		auto prefixes = Prefix::parse_list(iter);

		if (prefixes.has_error())
			return prefixes.error();

		if (iter->type() == TOKEN_IDENTIFIER)
		{
			auto identifier = Identifier::parse(iter);

			if (identifier.has_error())
				return identifier.error();

			auto postfixes = Postfix::parse_list(iter);

			if (postfixes.has_error())
				return postfixes.error();

			return PrimaryExpression(prefixes.unwrap(), postfixes.unwrap(), identifier.unwrap());
		}
		else if (iter->type() == TOKEN_LPAREN)
		{
			iter += 1;

			auto expression = Expression::parse(iter);

			if (expression.has_error())
				return expression.error();

			if (iter->type() != TOKEN_RPAREN)
			{
				errortf(*iter, "expected ')' after expression but got: %t", &(*iter));
				return ERROR_ARGUMENT;
			}

			iter += 1;
			auto postfixes = Postfix::parse_list(iter);

			if (postfixes.has_error())
				return postfixes.error();

			return PrimaryExpression(prefixes.unwrap(), postfixes.unwrap(), new Expression(expression.unwrap()));
		}
		
		auto constant = Constant::parse(iter);

		if (constant.has_error())
			return constant.error();

		auto postfixes = Postfix::parse_list(iter);

		if (postfixes.has_error())
			return postfixes.error();

		return PrimaryExpression(prefixes.unwrap(), postfixes.unwrap(), constant.unwrap());
	}

	void PrimaryExpression::print_tree(u32 depth) const
	{
		if (_prefixes.size() > 0)
			depth += 1;

		for (const auto& prefix : _prefixes)
			prefix.print_tree(depth - 1);

		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				_identifier.print_tree(depth);
				break;

			case PRIMARY_CONSTANT:
				_constant.print_tree(depth);
				break;

			case PRIMARY_EXPRESSION:
				_expression->print_tree(depth);
				break;
		}

		for (const auto& postfix : _postfixes)
			postfix.print_tree(depth + 1);
	}

	PrimaryExpression& PrimaryExpression::operator=(PrimaryExpression&& other)
	{
		_prefixes = std::move(other._prefixes);
		_postfixes = std::move(other._postfixes);
		_type = other._type;

		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				_identifier = std::move(other._identifier);
				break;

			case PRIMARY_CONSTANT:
				_constant = std::move(other._constant);
				break;

			case PRIMARY_EXPRESSION:
				_expression = other._expression;
				break;
		}

		other._type = PRIMARY_EXPRESSION;
		other._expression = nullptr;

		return *this;
	}

	PrimaryExpression& PrimaryExpression::operator=(const PrimaryExpression& other)
	{
		_prefixes = other._prefixes;
		_postfixes = other._postfixes;
		_type = other._type;

		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				_identifier = other._identifier;
				break;

			case PRIMARY_CONSTANT:
				_constant = other._constant;
				break;

			case PRIMARY_EXPRESSION:
				_expression = new Expression(*other._expression);
				break;
		}

		return *this;
	}
}
