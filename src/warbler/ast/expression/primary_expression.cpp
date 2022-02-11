#include <warbler/ast/expression/primary_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

// standard headers
#include <cassert>
#include <cstdlib>

namespace warbler::ast
{
	PrimaryExpression::PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Identifier&& identifier) :
	_prefixes(std::move(prefixes)),
	_postfixes(std::move(postfixes)),
	_identifier(std::move(identifier)),
	_type(PRIMARY_IDENTIFIER)
	{}

	PrimaryExpression::PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Constant&& constant) :
	_prefixes(std::move(prefixes)),
	_postfixes(std::move(postfixes)),
	_constant(std::move(constant)),
	_type(PRIMARY_CONSTANT)
	{}

	PrimaryExpression::PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Ptr<Expression>&& expression) :
	_prefixes(std::move(prefixes)),
	_postfixes(std::move(postfixes)),
	_expression(std::move(expression)),
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
				new(&_identifier) auto(std::move(other._identifier));
				break;

			case PRIMARY_CONSTANT:
				new(&_constant) auto(std::move(other._constant));
				break;

			case PRIMARY_EXPRESSION:
				new (&_expression) auto(std::move(other._expression));
				break;
		}
	}
	
	PrimaryExpression::~PrimaryExpression()
	{
		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				_identifier.~Identifier();
				break;

			case PRIMARY_CONSTANT:
				_constant.~Constant();
				break;

			case PRIMARY_EXPRESSION:
				_expression.~Ptr();
				break;
		}
	}

	Result<PrimaryExpression> PrimaryExpression::parse(TokenIterator& iter)
	{
		auto prefixes = Prefix::parse_list(iter);

		if (iter->type() == TOKEN_IDENTIFIER)
		{
			auto identifier = Identifier::parse(iter);

			if (identifier.has_error())
				return identifier.error();

			auto postfixes = Postfix::parse_list(iter);

			if (postfixes.has_error())
				return postfixes.error();

			return PrimaryExpression(std::move(prefixes), postfixes.unwrap(), identifier.unwrap());
		}
		else if (iter->type() == TOKEN_LPAREN)
		{
			iter += 1;

			auto expression = Expression::parse(iter);

			if (expression.has_error())
				return expression.error();

			if (iter->type() != TOKEN_RPAREN)
			{
				parse_error(iter, "expected ')' after expression");
				return ERROR_ARGUMENT;
			}

			iter += 1;

			auto postfixes = Postfix::parse_list(iter);

			if (postfixes.has_error())
				return postfixes.error();

			return PrimaryExpression { std::move(prefixes), postfixes.unwrap(), expression.unwrap() };
		}
		
		auto constant = Constant::parse(iter);

		if (constant.has_error())
			return constant.error();

		auto postfixes = Postfix::parse_list(iter);

		if (postfixes.has_error())
			return postfixes.error();

		return PrimaryExpression(std::move(prefixes), postfixes.unwrap(), constant.unwrap());
	}

	bool PrimaryExpression::validate(semantics::ModuleContext& context, bool expect_lvalue)
	{
		#pragma message("implement reference depth handling in validation")
		#pragma message("implement type handling in validation")

		switch (_type)
		{
			case PRIMARY_IDENTIFIER:
				if (context.
				if (!_identifier.validate(context))
					return false;
				break;

			case PRIMARY_CONSTANT:
				if (!_constant.validate(context))
					return false;
				break;

			case PRIMARY_EXPRESSION:
				if (!_expression->validate(context))
					return false;
				break;
		}
		

		auto is_rvalue = false;
		auto reference_depth = 0u; // TODO: infer from type

		for (i32 i = _prefixes.size() - 1; i >= 0; --i)
		{
			const auto& prefix = _prefixes[i];

			switch (prefix.type())
			{
				case PREFIX_REFERENCE:

					// ERROR if ravlue
					// OK for any type

					if (is_rvalue)
					{
						// ERROR cannot take refence of rvalue
					}

					is_rvalue = true;
					reference_depth += 1;
					break;

				case PREFIX_DEREFERENCE:
					if (reference_depth == 0)
					{
						print_error(prefix.location(), "dereferencing may only be done on pointer types");
						return false;
					}

					is_rvalue = false;
					break;

				case PREFIX_POSITIVE:
					is_rvalue = true;

					// ERROR if not integral
					break;

				case PREFIX_NEGATIVE:
					is_rvalue = true;
					// ERROR if not integral
					break;

				case PREFIX_BITWISE_NOT:
					is_rvalue = true;
					// ERROR if not integral or byte
					break;

				case PREFIX_BOOLEAN_NOT:
					is_rvalue = true;
					// ERROR if not boolean-ish					
					break;
			}

			if (prefix.type() == PREFIX_REFERENCE)
			{
				if (is_rvalue)
				{
					error_out(prefix.location());
					error_highlight(prefix.location());

					return false;
				}

				is_rvalue = true;
			}
		}


		return true;
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
		new (this) auto(std::move(other));
		return *this;
	}
}
