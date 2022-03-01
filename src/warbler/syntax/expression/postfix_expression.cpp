#include <warbler/syntax/expression/postfix_expression.hpp>

#include <warbler/util/print.hpp>
#include <warbler/syntax/expression/primary_expression.hpp>

// call parse then check for type
// not sure how to do this

namespace warbler::syntax
{
	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index) :
	_expression(std::move(expression)),
	_index(std::move(index)),
	_type(PostfixType::Index)
	{}

	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments) :
	_expression(std::move(expression)),
	_arguments(std::move(arguments)),
	_type(PostfixType::FunctionCall)
	{}

	PostfixExpression::PostfixExpression(Ptr<Expression>&& expression, Identifier&& member_name) :
	_expression(std::move(expression)),
	_member(MemberExpression { std::move(member_name), nullptr }),
	_type(PostfixType::Member)
	{}
 
	PostfixExpression::PostfixExpression(PostfixExpression&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case PostfixType::Index:
				new(&_index) auto(std::move(other._index));
				break;

			case PostfixType::FunctionCall:
				new(&_arguments) auto(std::move(other._arguments));
				break;

			case PostfixType::Member:
				new (&_member) auto(std::move(other._member));
				break;
		}
	}

	PostfixExpression::~PostfixExpression()
	{
		switch (_type)
		{
			case PostfixType::Index:
				_index.~Ptr();
				break;

			case PostfixType::FunctionCall:
				_arguments.~vector();
				break;

			case PostfixType::Member:
				_member.~MemberExpression();
				break;
		}
	}

	static Result<Array<Ptr<Expression>>> parse_arguments(lexicon::Token& token)
	{
		token.next();

		Array<Ptr<Expression>> arguments;

	parse_argument:

		if (token.type() != lexicon::TokenType::RightParenthesis)
		{
			auto res = Expression::parse(token.next());

			if (!res)
				return {};
			
			arguments.emplace_back(res.unwrap());

			if (token.type() == lexicon::TokenType::Comma)
			{
				token.next();
				goto parse_argument;
			}

			if (token.type() != lexicon::TokenType::RightParenthesis)
			{
				print_parse_error(token, "')' after function arguments");
				return {};
			}
		}

		token.next();

		return arguments;
	}
	
	Result<Ptr<Expression>> PostfixExpression::parse(lexicon::Token& token)
	{
		auto primary_expression = PrimaryExpression::parse(token);

		if (!primary_expression)
			return {};

		Ptr<Expression> expression = primary_expression.unwrap();

	parse_postfix:
		switch (token.type())
		{
			case lexicon::TokenType::LeftBracket:
			{
				auto res = Expression::parse(token.next());

				if (!res)
					return {};

				if (token.type() != lexicon::TokenType::RightBracket)
				{
					print_parse_error(token, "']' after index operation");
					return {};
				}

				token.next();

				expression = new PostfixExpression(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case lexicon::TokenType::LeftParenthesis:
			{
				auto res = parse_arguments(token.next());

				if (!res)
					return {};

				expression = new PostfixExpression(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case lexicon::TokenType::Dot:
			{
				token.next();

				auto res = Identifier::parse(token.next());

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

	// bool PostfixExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	if (!_expression->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	switch (_type)
	// 	{
	// 		case PostfixType::Index:
	// 			_index->validate(mod_ctx, func_ctx);
	// 			break;

	// 		case PostfixType::FunctionCall:
	// 			for (auto& arg : _arguments)
	// 			{
	// 				arg->validate(mod_ctx, func_ctx);
	// 			}
	// 			break;

	// 		case PostfixType::Member:
	// 		{
	// 			auto *expr_type = _expression->get_type();

	// 			_member.definition = expr_type->definition()->get_member(_member.name.text());

	// 			if (_member.definition == nullptr)
	// 			{
	// 				print_error(_member.name.token(), "'" + _member.name.text() + "' is not a member of type '" + expr_type->text() + "'");
	// 				return false;
	// 			}
	// 			break;
	// 		}
	// 	}

	// 	return true;
	// }

	Type *PostfixExpression::get_type()
	{
		// switch (_type)
		// {
		// 	case PostfixType::Index:
		// 		break;

		// 	case PostfixType::FunctionCall:
		// 		return 
		// 		break;

		// 	case PostfixType::Member:
				
		// 		break;
		// }
		throw std::runtime_error("PostfixExpression::" + String(__func__) + " is not implemented yet");
	}

	const lexicon::Token& PostfixExpression::token() const
	{
		throw std::runtime_error("PostfixExpression::" + String(__func__) + " is not implemented yet");
	}

	void PostfixExpression::print_tree(u32 depth) const
	{
		_expression->print_tree(depth);

		switch (_type)
		{
			case PostfixType::Index:
				print_branch(depth + 1, "[");
				_index->print_tree(depth + 2);
				print_branch(depth + 1, "]");
				break;

			case PostfixType::FunctionCall:
				print_branch(depth + 1, "(");

				for (const auto& arg : _arguments)
					arg->print_tree(depth + 2);

				print_branch(depth + 1, ")");
			break;

			case PostfixType::Member:
				print_branch(depth + 1, "." + _member.name.token().text());
				break;
		}
	}
}
