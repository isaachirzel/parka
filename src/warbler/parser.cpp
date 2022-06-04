#include <warbler/parser.hpp>

#include <warbler/util/print.hpp>
#include <warbler/directory.hpp>
#include <cassert>

namespace warbler
{
	Result<ExpressionSyntax> parse_additive_expression(Token& token)
	{
		auto lhs = parse_multiplicative_expression(token);

		if (!lhs)
			return {};

		Array<AdditiveRhsSyntax> RhsSyntax;

		while (true)
		{
			AdditiveType type;
			if (token.type() == TokenType::Plus)
			{
				type = AdditiveType::Add;
			}
			else if (token.type() == TokenType::Minus)
			{
				type = AdditiveType::Add;
			}
			else
			{
				break;
			}

			token.increment();

			auto res = parse_multiplicative_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(AdditiveRhsSyntax { res.unwrap(), type });
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(AdditiveExpressionSyntax {lhs.unwrap(), std::move(RhsSyntax) });
	}

	Result<ExpressionSyntax> parse_bitwise_and_expression(Token& token)
	{
		auto lhs = parse_equality_expression(token);

		if (!lhs)
			return {};

		Array<ExpressionSyntax> RhsSyntax;

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto res = parse_equality_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(res.unwrap());
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BitwiseAndExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_bitwise_or_expression(Token& token)
	{
		auto lhs = parse_bitwise_xor_expression(token);

		if (!lhs)
			return {};

		Array<ExpressionSyntax> RhsSyntax;

		while (token.type() == TokenType::Pipeline)
		{
			token.increment();
			auto res = parse_bitwise_xor_expression(token);
			
			if (!res)
				return {};

			RhsSyntax.emplace_back(res.unwrap());
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BitwiseOrExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_bitwise_xor_expression(Token& token)
	{
		auto lhs = parse_bitwise_and_expression(token);

		if (!lhs)
			return {};

		Array<ExpressionSyntax> RhsSyntax;

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto res = parse_bitwise_and_expression(token);
			
			if (!res)
				return {};

			RhsSyntax.emplace_back(res.unwrap());
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BitwiseXorExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_boolean_and_expression(Token& token)
	{
		auto lhs = parse_bitwise_or_expression(token);

		if (!lhs)
			return {};

		Array<ExpressionSyntax> RhsSyntax;

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto res = parse_bitwise_or_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(res.unwrap());
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BooleanAndExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_boolean_or_expression(Token& token)
	{
		auto lhs = parse_boolean_and_expression(token);

		if (!lhs)
			return {};

		Array<ExpressionSyntax> RhsSyntax;

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto res = parse_boolean_and_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(res.unwrap());
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BooleanOrExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_conditional_expression(Token& token)
	{
		auto lhs = parse_boolean_or_expression(token);

		if (!lhs)
			return {};

		if (token.type() != TokenType::KeywordThen)
			return lhs.unwrap();

		token.increment();

		auto true_case = parse_boolean_or_expression(token);

		if (!true_case)
			return {};

		if (token.type() != TokenType::KeywordElse)
		{
			print_parse_error(token, "'else' or false case");
			return {};
		}

		token.increment();

		auto false_case = parse_boolean_or_expression(token);

		if (!false_case)
			return {};

		return ExpressionSyntax(ConditionalExpressionSyntax(lhs.unwrap(), true_case.unwrap(), false_case.unwrap()));
	}

	Result<ExpressionSyntax> parse_equality_expression(Token& token)
	{
		auto lhs = parse_relational_expression(token);
		 
		if (!lhs)
			return {};

		Array<EqualityRhsSyntax> RhsSyntax;

		while (true)
		{
			bool should_break = false;

			EqualityType type;
			switch (token.type())
			{
				case TokenType::Equals:
					type = EqualityType::Equals;
					break;

				case TokenType::NotEquals:
					type = EqualityType::NotEquals;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			token.increment();

			auto res = parse_relational_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(EqualityRhsSyntax { res.unwrap(), type });
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(EqualityExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}


	Result<ExpressionSyntax> parse_multiplicative_expression(Token& token)
	{
		auto lhs = parse_prefix_expression(token);

		if (!lhs)
			return {};

		Array<MultiplicativeRhsSyntax> RhsSyntax;

		while (true)
		{
			bool should_break = false;

			MultiplicativeType type;
			switch (token.type())
			{
				case TokenType::Modulus:
					type = MultiplicativeType::Modulus;
					break;

				case TokenType::Asterisk:
					type = MultiplicativeType::Multiply;
					break;

				case TokenType::Slash:
					type = MultiplicativeType::Divide;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			token.increment();

			auto res = parse_prefix_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(MultiplicativeRhsSyntax { res.unwrap(), type });
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(MultiplicativeExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<Array<ExpressionSyntax>> parse_arguments(Token& token)
	{
		token.increment();

		Array<ExpressionSyntax> arguments;

	parse_argument:

		if (token.type() != TokenType::RightParenthesis)
		{
			token.increment();
			
			auto res = parse_expression(token);

			if (!res)
				return {};
			
			arguments.emplace_back(res.unwrap());

			if (token.type() == TokenType::Comma)
			{
				token.increment();
				goto parse_argument;
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				print_parse_error(token, "')' after function arguments");
				return {};
			}
		}

		token.increment();

		return arguments;
	}

	Result<ExpressionSyntax> parse_postfix_expression(Token& token)
	{
		auto primary_expression = parse_primary_expression(token);

		if (!primary_expression)
			return {};

		ExpressionSyntax expression = primary_expression.unwrap();

	parse_postfix:
		switch (token.type())
		{
			case TokenType::LeftBracket:
			{
				token.increment();

				auto res = parse_expression(token);

				if (!res)
					return {};

				if (token.type() != TokenType::RightBracket)
				{
					print_parse_error(token, "']' after index operation");
					return {};
				}

				token.increment();

				expression = PostfixExpressionSyntax(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case TokenType::LeftParenthesis:
			{
				token.increment();

				auto res = parse_arguments(token);

				if (!res)
					return {};

				expression = PostfixExpressionSyntax(std::move(expression), res.unwrap());
				goto parse_postfix;
			}

			case TokenType::Dot:
			{
				token.increment();
			
				if (token.type() != TokenType::Identifier)
				{
					print_parse_error(token, "member, method, or property name");
					return {};
				}

				auto name = token;

				token.increment();
				
				expression = PostfixExpressionSyntax { std::move(expression), name };
				goto parse_postfix;
			}
			
			default:
				break;
		}

		return expression;
	}

	Result<ExpressionSyntax> parse_prefix_expression(Token& token)
	{
		PrefixType type;

		switch (token.type())
		{
			case TokenType::Ampersand:
				type = PrefixType::Reference;
				break;

			case TokenType::Asterisk:
				type = PrefixType::Dereference;
				break;

			case TokenType::Plus:
				type = PrefixType::Positive;
				break;

			case TokenType::Minus:
				type = PrefixType::Negative;
				break;

			case TokenType::BitwiseNot:
				type = PrefixType::BitwiseNot;
				break;

			case TokenType::BooleanNot:
				type = PrefixType::BooleanNot;
				break;

			default:
				return parse_postfix_expression(token);
		}

		auto prefix = token;

		token.increment();

		auto res = parse_prefix_expression(token);

		if (!res)
			return {};

		return ExpressionSyntax { PrefixExpressionSyntax(prefix, res.unwrap(), type) };
	}

	Result<ExpressionSyntax> parse_primary_expression(Token& token)
	{
		if (token.type() == TokenType::Identifier)
		{
			auto symbol = parse_symbol(token);

			if (!symbol)
				return {};

			return symbol.unwrap();
		}
		else if (token.type() == TokenType::LeftParenthesis)
		{
			token.increment();

			auto expression = parse_expression(token);

			if (!expression)
				return {};

			if (token.type() != TokenType::RightParenthesis)
			{
				print_parse_error(token, "expected ')' after primary sub-expression");
				return {};
			}

			token.increment();

			return expression.unwrap();
		}
		else
		{
			auto constant = parse_constant(token);

			if (!constant)
				return {};

			return constant.unwrap();
		}
	}

	Result<ExpressionSyntax> parse_relational_expression(Token& token)
	{
		auto lhs = parse_bit_shift_expression(token);

		if (!lhs)
			return {};

		Array<RelationalRhsSyntax> RhsSyntax;

		while (true)
		{
			bool should_break = false;

			RelationalType type;
			switch (token.type())
			{
				case TokenType::GreaterThan:
					type = RelationalType::GreaterThan;
					break;

				case TokenType::LessThan:
					type = RelationalType::LessThan;
					break;

				case TokenType::GreaterThanOrEqualTo:
					type = RelationalType::GreaterThanOrEqualTo;
					break;

				case TokenType::LessThanOrEqualTo:
					type = RelationalType::LessThanOrEqualTo;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			token.increment();

			auto res = parse_bit_shift_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(RelationalRhsSyntax { res.unwrap(), type });
		}

		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(RelationalExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	Result<ExpressionSyntax> parse_bit_shift_expression(Token& token)
	{
		auto lhs = parse_additive_expression(token);

		if (!lhs)
			return {};

		Array<BitShiftRhsSyntax> RhsSyntax;

		while (true)
		{
			bool should_break = false;
			BitShiftType type;

			switch (token.type())
			{
				case TokenType::LeftBitShift:
					type = BitShiftType::Left;
					break;

				case TokenType::RightBitShift:
					type = BitShiftType::Right;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;
			
			token.increment();

			auto res = parse_additive_expression(token);

			if (!res)
				return {};

			RhsSyntax.emplace_back(BitShiftRhsSyntax { res.unwrap(), type });
		}
		
		if (RhsSyntax.empty())
			return lhs.unwrap();

		return ExpressionSyntax(BitShiftExpressionSyntax(lhs.unwrap(), std::move(RhsSyntax)));
	}

	static Result<ExpressionSyntax> parse_character(Token& token)
	{
		if (token.length() != 3)
		{
			print_error(token, "character literals may only contain 1 character");
			return {};
		}

		auto character = token[1];

		token.increment();

		return ExpressionSyntax(ConstantSyntax(token, character));
	}

	static Result<ExpressionSyntax> parse_float(Token& token)
	{
#pragma message "TODO: account for multiple decimals when parsing float"
		f64 value = 0.0;
		for (size_t i = 0; i < token.length(); ++i)
		{
			if (token[i] != '.')
			{
				value = value * 10.0 + (token[i] - '0');
			}
			else
			{
				i += 1;

				f64 decimal = 0.0;
				f64 place = 1.0;

				while (i < token.length())
				{
					decimal = decimal * 10.0 + (token[i] - '0');
					place *= 10.0;
					++i;
				}
				
				value += (decimal / place);
				break;
			}
		}
		
		const auto t = token;

		token.increment();

		return ExpressionSyntax(ConstantSyntax(t, value));
	}

	static ExpressionSyntax parse_string(Token& token)
	{
		const auto t = token;

		token.increment();

		auto text = token.file().get_text(token.pos() + 1, token.length() - 2);

		return ConstantSyntax(t, std::move(text));
	}

	static ExpressionSyntax parse_integer(Token& token)
	{
		#pragma message "TODO: handle potential for too many numbers in integer literal"

		u64 value = 0;

		for (size_t i = 0; i < token.length(); ++i)
			value = value * 10 + (token[i] - '0');

		const auto t = token;

		token.increment();

		return ConstantSyntax(t, value);
	}

	Result<ExpressionSyntax> parse_constant(Token& token)
	{
		switch (token.type())
		{
			case TokenType::CharLiteral:
				return parse_character(token);

			case TokenType::StringLiteral:
				return parse_string(token);

			case TokenType::IntegerLiteral:
				return parse_integer(token);

			case TokenType::BinaryLiteral:
			case TokenType::HexadecimalLiteral:
			case TokenType::OctalLiteral:
				throw std::runtime_error("binary, hexadecimal, and octal parsing are not implemented yet");
				break;

			case TokenType::FloatLiteral:
				return parse_float(token);

			case TokenType::KeywordTrue:
			{
				const auto t = token;
				token.increment();
				return ExpressionSyntax(ConstantSyntax(t, true));
			}

			case TokenType::KeywordFalse:
			{
				const auto t = token;
				token.increment();
				return ExpressionSyntax(ConstantSyntax(t, false));
			}

			default:
				break;
		}

		print_parse_error(token, "constant");
		return {};
	}

	Result<ExpressionSyntax> parse_symbol(Token& token)
	{
		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "symbol");
			return {};
		}

		auto symbol = token;

		token.increment();

		return ExpressionSyntax(SymbolSyntax(symbol));
	}

	Result<FunctionSyntax> parse_function(Token& token)
	{
		if (token.type() != TokenType::KeywordFunction)
		{
			print_parse_error(token, "'function'");
			return {};
		}

		token.increment();

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "function name");
			return {};
		}

		auto name = token;

		token.increment();

		auto signature = parse_function_signature(token);

		if (!signature)
			return {};

		if (token.type() != TokenType::LeftBrace)
		{
			print_parse_error(token, "function body");
			return {};
		}
	
		auto body = parse_block_statement(token);

		if (!body)
			return {};

		return FunctionSyntax(name, signature.unwrap(), body.unwrap());
	}

	Result<ParameterSyntax> parse_parameter(Token& token)
	{
		bool is_mutable = false;

		if (token.type() == TokenType::KeywordMut)
		{
			is_mutable = true;
			token.increment();
		}

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "parameter name");
			return {};
		}

		auto name = token;

		token.increment();

		if (token.type() != TokenType::Colon)
		{
			print_parse_error(token, ":", "parameters require a valid type");
			return {};
		}

		token.increment();

		auto type = parse_type_annotation(token);

		if (!type)
			return {};

		return ParameterSyntax(name, type.unwrap(), is_mutable);
	}

	Result<Array<ParameterSyntax>> parse_parameter_list(Token& token)
	{
		if (token.type() != TokenType::LeftParenthesis)
		{
			print_parse_error(token, "'(' after function name");
			return {};
		}

		Array<ParameterSyntax> parameters;

		token.increment();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto res = parse_parameter(token);

				if (!res)
					return {};

				parameters.emplace_back(res.unwrap());

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				print_parse_error(token, "')'", "Invalid tokens in parameter list");
				return {};
			}
		}

		token.increment();

		return parameters;
	}

	Result<FunctionSignatureSyntax> parse_function_signature(Token& token)
	{
		auto parameters = parse_parameter_list(token);

		if (!parameters)
			return {};

		if (token.type() != TokenType::Colon)
		{
			print_parse_error(token, "type", "Parameters cannot be declared without a type.");
			return {};
		}

		token.increment();

		auto type = parse_type_annotation(token);

		if (!type)
			return {};

		return FunctionSignatureSyntax(parameters.unwrap(), type.unwrap());
	}

	Result<AssignmentSyntax> parse_assignment(Token& token)
	{
		token.increment();

		auto lhs = parse_expression(token);

		if (!lhs)
			return {};

		AssignmentType type;
		switch (token.type())
		{
			case TokenType::Assign:
				type = AssignmentType::Become;
				break;

			case TokenType::MultiplyAssign:
				type = AssignmentType::Multiply;
				break;

			case TokenType::DivideAssign:
				type = AssignmentType::Divide;
				break;

			case TokenType::ModulusAssign:
				type = AssignmentType::Modulus;
				break;

			case TokenType::AddAssign:
				type = AssignmentType::Add;
				break;

			case TokenType::SubtractAssign:
				type = AssignmentType::Subtract;
				break;

			case TokenType::LeftBitShiftAssign:
				type = AssignmentType::LeftBitShift;
				break;

			case TokenType::RightBitShiftAssign:
				type = AssignmentType::RightBitShift;
				break;

			case TokenType::BitwiseAndAssign:
				type = AssignmentType::BitwiseAnd;
				break;

			case TokenType::BitwiseOrAssign:
				type = AssignmentType::BitwiseOr;
				break;

			case TokenType::BitwiseXorAssign:
				type = AssignmentType::BitwiseXor;
				break;

			default:
				print_parse_error(token, "expected assignment operator after primary expression");
				return {};
		}

		token.increment();

		auto RhsSyntax = parse_expression(token);

		if (!RhsSyntax)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			print_parse_error(token, "';' after assignment");
			return {};
		}

		token.increment();

		return AssignmentSyntax(lhs.unwrap(), RhsSyntax.unwrap(), type);
	}

	Result<BlockStatementSyntax> parse_block_statement(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			print_parse_error(token, "compound statement starting with '{'");
			return {};
		}

		token.increment();

		Array<Box<StatementSyntax>> statements;

		while (token.type() != TokenType::RightBrace)
		{
			auto res = parse_statement(token);


			if (!res)
				return {};

			statements.emplace_back(Box<StatementSyntax>(res.unwrap()));
		}

		token.increment();

		return BlockStatementSyntax(std::move(statements));
	}

	Result<DeclarationSyntax> parse_declaration(Token& token)
	{
		if (token.type() != TokenType::KeywordVar)
		{
			print_parse_error(token, "var");
			return {};
		}

		token.increment();
		
		auto declaration = parse_variable(token);

		if (!declaration)
			return {};

		if (token.type() != TokenType::Assign)
		{
			print_parse_error(token, "expected '=' after declaration");
			return {};
		}

		token.increment();

		auto value = parse_expression(token);

		if (!value)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			print_parse_error(token, "expected ';' after declaration");
			return {};
		}

		token.increment();

		return DeclarationSyntax(declaration.unwrap(), value.unwrap());
	}

	Result<ExpressionStatementSyntax> parse_expression_statement(Token& token)
	{
		token.increment();

		auto expression = parse_expression(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			print_parse_error(token, "expected ';' after expression");
			return {};
		}

		token.increment();

		return ExpressionStatementSyntax(expression.unwrap());
	}

	Result<IfStatementSyntax> parse_if_statement(Token& token)
	{
		token.increment();
		
		auto condition = parse_expression(token);

		if (!condition)
			return {};

		token.increment();

		auto then_body = parse_block_statement(token);

		if (!then_body)
			return {};

		if (token.type() == TokenType::KeywordElse)
		{
			token.increment();

			if (token.type() == TokenType::KeywordIf)
			{
				token.increment();

				auto else_if = parse_if_statement(token);

				if (!else_if)
					return {};

				return IfStatementSyntax(condition.unwrap(), then_body.unwrap(), new IfStatementSyntax(else_if.unwrap()));
			}
			else
			{
				token.increment();

				auto else_body = parse_block_statement(token);

				if (!else_body)
					return {};

				return IfStatementSyntax { condition.unwrap(), then_body.unwrap(), else_body.unwrap() };
			}
		}
		
		return IfStatementSyntax(condition.unwrap(), then_body.unwrap());
	}

	Result<StatementSyntax> parse_statement(Token& token)
	{
		switch (token.type())
		{
			case TokenType::KeywordVar:
			{
				auto res = parse_declaration(token);

				if (!res)
					return {};

				return StatementSyntax(res.unwrap());
			}

			//case TokenType::MATCH:
			case TokenType::KeywordIf:
			{
				auto res = parse_if_statement(token);

				if (!res)
					return {};

				return StatementSyntax(res.unwrap());
			}

			// case TokenType::LOOP:
			// case TokenType::WHILE:
			// case TokenType::FOR:
			// 	return parse_statement<LoopStatementSyntax>(iter);

			// case TokenType::CONTINUE:
			// case TokenType::BREAK:
			// case TokenType::RETURN:
			// 	return parse_statement<JumpStatementSyntax>(iter);

			default:
				break;
		}

		token.increment();

		auto res = parse_expression(token);

		if (!res)
			return {};

		return StatementSyntax(res.unwrap());
	}

	Result<TypeSyntax> parse_type(Token& token)
	{
		assert(token.type() == TokenType::KeywordType);

		token.increment();

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "type name");
			return {};
		}

		auto name_token = token;

		token.increment();

		if (token.type() != TokenType::Colon)
		{
			print_parse_error(token, "':' after type name");
			return {};
		}

		token.increment();

		switch (token.type())
		{
			case TokenType::KeywordStruct:
			{
				auto res = parse_struct(token);

				if (!res)
					return {};

				return TypeSyntax(name_token, res.unwrap());
			}

			default:
				#pragma message "Implement the ability to have other types as type definitions"
				print_parse_error(token, "type definition or base type");
				return {};
		}
	}

	Result<MemberSyntax> parse_member(Token& token)
	{
		auto is_public = false;

		if (token.type() == TokenType::KeywordPublic)
		{
			is_public = true;
			token.increment();
		}
		else if (token.type() == TokenType::KeywordPrivate)
		{
			token.increment();
		}

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "member name");
			print_note("Trailing commas are not allowed.");
			return {};
		}

		auto name_token = token;

		token.increment();

		if (token.type() != TokenType::Colon)
		{
			print_parse_error(token, "':' after member name");
			return {};
		}
		
		token.increment();

		auto type = parse_type_annotation(token);

		if (!type)
			return {};

		return MemberSyntax(name_token, type.unwrap(), is_public);
	}

	Result<StructSyntax> parse_struct(Token& token)
	{
		assert(token.type() == TokenType::KeywordStruct);

		token.increment();

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "struct name");
			return {};
		}

		auto name = token;

		token.increment();

		if (token.type() != TokenType::LeftBrace)
		{
			print_parse_error(token, "'{' before struct body");
			return {};
		}

		token.increment();

		Array<MemberSyntax> members;

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = parse_member(token);

				if (!member)
					return {};

				members.emplace_back(member.unwrap());

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightBrace)
			{
				print_parse_error(token, "'}' after struct body");
				return {};
			}
		}

		token.increment();

		return StructSyntax(name, members);
	}

	Result<LabelSyntax> parse_label(Token& token)
	{
		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "label identifer");
			return {};
		}

		auto label = token;

		token.increment();

		if (token.type() != TokenType::Colon)
		{
			print_parse_error(token, "':' after label");
			return {};
		}

		token.increment();

		return LabelSyntax(label);
	}

	Result<TypeAnnotationSyntax> parse_type_annotation(Token& token)
	{
		Array<PtrSyntax> ptr_mutability;

		const Token start_token = token;

		while (token.type() == TokenType::Asterisk)
		{
			token.increment();

			if (token.type() == TokenType::KeywordMut)
			{
				ptr_mutability.emplace_back(PtrSyntax { token, true });
				token.increment();
			}
			else
			{
				ptr_mutability.emplace_back(PtrSyntax { token, false });
			}
		}

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "type");
			return {};
		}
		
		const auto base_type = token;

		token.increment();

		#pragma message "fix parsing of Syntax"
		return TypeAnnotationSyntax(base_type, std::move(ptr_mutability));
	}

	Result<VariableSyntax> parse_variable(Token& token)
	{
		auto is_mutable = false;

		if (token.type() == TokenType::KeywordMut)
		{
			is_mutable = true;
			token.increment();
		}

		if (token.type() != TokenType::Identifier)
		{
			print_parse_error(token, "variable name");
			return {};
		}

		auto name = token;

		token.increment();

		Optional<TypeAnnotationSyntax> type;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			auto res = parse_type_annotation(token);

			if (!res)
				return {};

			type = res.unwrap();
		}

		return VariableSyntax(name, std::move(type), is_mutable);
	}

	Result<ModuleSyntax> parse_module(const File& file)
	{
		Array<FunctionSyntax> functions;
		Array<StructSyntax> structs;
		auto token = Token::get_initial(file);

		while (true)
		{
			switch (token.type())
			{
				case TokenType::KeywordFunction:
				{
					auto function = parse_function(token);

					if (!function)
						return {};

					functions.emplace_back(function.unwrap());
					continue;
				}
				case TokenType::KeywordStruct:
				{
					auto res = parse_struct(token);

					if (!res)
						return {};

					structs.emplace_back(res.unwrap());
					continue;
				}

				case TokenType::EndOfFile:
					break;

				default:
					print_parse_error(token, "type or function definition");
					return {};
			}
			break;
		}

		return ModuleSyntax { std::move(functions), std::move(structs) };
	}

	Result<PackageSyntax> parse_package(const Directory& directory)
	{
		Array<FunctionSyntax> functions;
		Array<StructSyntax> structs;

		for (const auto& file : directory.files())
		{
			auto res = parse_module(file);

			if (!res)
				return {};

			auto mod = res.unwrap();

			functions.reserve(functions.size() + mod.functions.size());

			for (auto& function : mod.functions)
			{
				functions.emplace_back(std::move(function));
			}

			structs.reserve(structs.size() + mod.structs.size());

			for (auto& type : mod.structs)
			{
				structs.emplace_back(std::move(type));
			}
		}

		return PackageSyntax(directory.path(), std::move(functions), std::move(structs));
	}

	Result<ProgramSyntax> parse(const Array<Directory>& directories)
	{
		Array<PackageSyntax> packages;

		for (const auto& directory : directories)
		{
			auto package = parse_package(directory);

			if (!package)
				return {};

			packages.emplace_back(package.unwrap());
		}

		if (packages.size() == 0)
		{
			// TODO: update this error
			print_error("No source files passed to compiler.");
			return {};
		}

		return ProgramSyntax(std::move(packages));
	}
}
