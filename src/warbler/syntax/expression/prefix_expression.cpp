#include <warbler/syntax/expression/prefix_expression.hpp>

#include <warbler/syntax/expression/postfix_expression.hpp>

// check for type then parse

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	PrefixExpression::PrefixExpression(const lexicon::Token& token, Ptr<Expression>&& expression, PrefixType type) :
	_token(token),
	_expression(std::move(expression)),
	_type(type)
	{}

	Result<Ptr<Expression>> PrefixExpression::parse(lexicon::Token& token)
	{
		PrefixType type;

		switch (token.type())
		{
			case lexicon::TokenType::Ampersand:
				type = PrefixType::Reference;
				break;

			case lexicon::TokenType::Asterisk:
				type = PrefixType::Dereference;
				break;

			case lexicon::TokenType::Plus:
				type = PrefixType::Positive;
				break;

			case lexicon::TokenType::Minus:
				type = PrefixType::Negative;
				break;

			case lexicon::TokenType::BitwiseNot:
				type = PrefixType::BitwiseNot;
				break;

			case lexicon::TokenType::BooleanNot:
				type = PrefixType::BooleanNot;
				break;

			default:
				return PostfixExpression::parse(token);
		}

		auto prefix = token;
		auto res = parse(token.next());

		if (!res)
			return {};

		auto *ptr = new PrefixExpression(prefix, res.unwrap(), type);

		return Ptr<Expression>(ptr);
	}

	// void PrefixExpression::print_tree(u32 depth) const
	// {
	// 	switch (_type)
	// 	{
	// 		case PrefixType::Reference:
	// 			print_branch(depth, "&");
	// 			break;

	// 		case PrefixType::Dereference:
	// 			print_branch(depth, "*");
	// 			break;

	// 		case PrefixType::Positive:
	// 			print_branch(depth, "+");
	// 			break;

	// 		case PrefixType::Negative:
	// 			print_branch(depth, "-");
	// 			break;

	// 		case PrefixType::BitwiseNot:
	// 			print_branch(depth, "~");
	// 			break;

	// 		case PrefixType::BooleanNot:
	// 			print_branch(depth, "!");
	// 			break;
	// 	}

	// 	_expression->print_tree(depth + 1);
	// }

	// bool PrefixExpression::validate(semantics::ModuleContext& module, semantics::FunctionContext& function)
	// {
	// 	throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	// }

	// Type *PrefixExpression::get_type()
	// {
	// 	throw std::runtime_error("PrefixExpression::" + String(__func__) + " is not implemented");
	// }
}
