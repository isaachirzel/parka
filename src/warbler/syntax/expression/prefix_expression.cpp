#include <warbler/syntax//expression/prefix_expression.hpp>

#include <warbler/syntax//expression/postfix_expression.hpp>

// check for type then parse

namespace warbler::syntax
{
	PrefixExpression::PrefixExpression(Ptr<Expression>&& expression, PrefixType type) :
	_expression(std::move(expression)),
	_type(type)
	{}

	Result<Ptr<Expression>> PrefixExpression::parse(TokenIterator& iter)
	{
		PrefixType type;

		switch (iter->type())
		{
			case TOKEN_AMPERSAND:
				type = PREFIX_REFERENCE;
				break;

			case TOKEN_ASTERISK:
				type = PREFIX_DEREFERENCE;
				break;

			case TOKEN_PLUS:
				type = PREFIX_POSITIVE;
				break;

			case TOKEN_MINUS:
				type = PREFIX_NEGATIVE;
				break;

			case TOKEN_BITWISE_NOT:
				type = PREFIX_BITWISE_NOT;
				break;

			case TOKEN_BOOLEAN_NOT:
				type = PREFIX_BOOLEAN_NOT;
				break;

			default:
				return PostfixExpression::parse(iter);
		}

		iter += 1;

		auto res = parse(iter);

		if (!res)
			return {};

		return Ptr<Expression> { new PrefixExpression(res.unwrap(), type) };
	}

	bool PrefixExpression::validate(semantics::ModuleContext& module, semantics::FunctionContext& function)
	{
		throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	}

	Type *PrefixExpression::get_type()
	{
		throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	}

	const Location& PrefixExpression::location() const
	{
		throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	}

	void PrefixExpression::print_tree(u32 depth) const
	{
		throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	}
}
