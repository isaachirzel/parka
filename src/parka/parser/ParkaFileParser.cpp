#include "parka/parser/ParkaFileParser.hpp"
#include "parka/ast/BinaryExpression.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/BoolLiteral.hpp"
#include "parka/ast/CallExpression.hpp"
#include "parka/ast/CharLiteral.hpp"
#include "parka/ast/ConditionalExpression.hpp"
#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ast/ExpressionStatement.hpp"
#include "parka/ast/FloatLiteral.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ast/IntegerLiteral.hpp"
#include "parka/ast/JumpStatement.hpp"
#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/ast/PrefixExpression.hpp"
#include "parka/ast/StringLiteral.hpp"
#include "parka/ast/SubscriptExpression.hpp"
#include "parka/enum/JumpType.hpp"
#include "parka/enum/PrefixType.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ast;

namespace parka::parser
{
	Optional<Identifier> ParkaFileParser::parseIdentifier()
	{
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "identifier");
			return {};
		}

		auto identifier = Identifier(token);

		token.increment();

		return identifier;
	}

	bool ParkaFileParser::parseAbsolute()
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();
		return true;
	}

	Optional<QualifiedIdentifier> ParkaFileParser::parseQualifiedIdentifier()
	{
		auto start = Snippet(token);
		auto isAbsolute = parseAbsolute();
		auto parts = Array<Identifier>(8);
		
		while (true)
		{
			auto identifier = parseIdentifier();

			if (!identifier)
				return {};

			parts.push(*identifier);

			if (token.type() == TokenType::Scope)
			{
				token.increment();
				continue;
			}

			break;
		}

		// Parts is guaranteed to be at least 1 long
		auto snippet = start + parts.back().snippet();
		auto qualifiedIdentifier = QualifiedIdentifier(snippet, std::move(parts), isAbsolute);

		return qualifiedIdentifier;
	}

	Optional<char> ParkaFileParser::parseChar()
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			log::parseError(token, "character");
			return {};
		}

		if (token.snippet().length() != 3)
		{
			log::error(token, "character literals may only contain 1 character", nullptr);
			return {};
		}

		auto character = token[0];

		return character;
	}

	ExpressionAst *ParkaFileParser::parseCharLiteral()
	{
		auto value = parseChar();

		if (!value)
			return {};

		auto *syntax = new CharLiteralAst(token, *value);

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseStringLiteral()
	{
		if (token.type() != TokenType::StringLiteralAst)
		{
			log::parseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralAst(token);

		token.increment();

		return syntax;
	}

	Optional<bool> ParkaFileParser::parseBool()
	{
		auto type = KeywordAst::getKeywordType(token);

		switch (type)
		{
			case KeywordType::True:
				return true;

			case KeywordType::False:
				return false;

			default:
				break;
		}

		log::parseError(token, "`true` or `false`");
		
		return {};
	}

	ExpressionAst *ParkaFileParser::parseBoolLiteral()
	{
		auto value = parseBool();

		if (!value)
			return {};

		auto *syntax = new BoolLiteralAst(token, *value);

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseFloatLiteral()
	{
		if (token.type() != TokenType::FloatLiteralAst)
		{
			log::parseError(token, "float");
			return nullptr;
		}

		auto *syntax = new FloatLiteralAst(token);

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseIntegerLiteral()
	{
		if (token.type() != TokenType::IntegerLiteralAst)
		{
			log::parseError(token, "integer");
			return {};
		}

		auto *syntax = new IntegerLiteralAst(token);

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseLiteral()
	{
		switch (token.type())
		{
			case TokenType::CharacterLiteral:
				return parseCharLiteral();

			case TokenType::StringLiteralAst:
				return parseStringLiteral();

			case TokenType::IntegerLiteralAst:
				return parseIntegerLiteral();

			case TokenType::FloatLiteralAst:
				return parseFloatLiteral();

			case TokenType::Identifier:
				return parseBoolLiteral();

			default:
				break;
		}
		
		log::parseError(token, "literal");
		
		return {};
	}

	ExpressionAst *ParkaFileParser::parseIdentifierExpression()
	{
		auto identifier = parseQualifiedIdentifier();
		auto *syntax = new IdentifierExpressionAst(*identifier);

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseBlockExpression()
	{
		if (token.type() != TokenType::LeftBrace)
		{
			log::parseError(token, "'{' before block");

			return {};
		}

		auto first = Token(token);

		token.increment();

		// TODO: Add initial capacity
		auto statements = Array<StatementAst*>();

		while (token.type() != TokenType::RightBrace)
		{
			auto *statement = parseStatement();

			if (!statement)
				return {};

			statements.push(statement);
		}

		auto last = Token(token);

		token.increment();

		auto *syntax = new BlockExpressionAst(first + last, std::move(statements));

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseExpression()
	{
		if (token.type() == TokenType::LeftBrace)
			return parseBlockExpression();

		return parseAssignmentExpression();
	}

	ExpressionAst *ParkaFileParser::parseEnclosedExpression()
	{
		token.increment();

		auto *expression = parseExpression();

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			log::parseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	ExpressionAst *ParkaFileParser::parsePrimaryExpression()
	{
		switch (token.type())
		{
			case TokenType::Identifier:
				return parseIdentifierExpression();

			case TokenType::LeftParenthesis:
				return parseEnclosedExpression();

			default:
				return parseLiteral();
		}
	}

	ExpressionAst *ParkaFileParser::parseCallExpression(ExpressionAst& primary)
	{
		auto first = Token(token);
		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto *argument = parseExpression();

				if (!argument)
					return {}; // TODO: Continue to next argument by checking for ','

				arguments.push(argument);

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				log::parseError(token, "')' after argument list");

				return {};
			}
		}

		auto snippet = first + token;

		token.increment();

		auto *syntax = new CallExpressionAst(snippet, primary, std::move(arguments));

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseSubscriptExpression(ExpressionAst& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			log::parseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = parseExpression();

		if (!index)
			return {};


		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		auto snippet = primary.snippet() + Snippet(token);
		auto *syntax = new SubscriptExpressionAst(snippet, primary, *index);

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseMemberAccessExpression(ExpressionAst& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			log::parseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionAst(primary, Identifier(token));

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parsePostfixExpression()
	{
		auto postfix = parsePrimaryExpression();

		while (true)
		{
			if (!postfix)
				return {};
				
			switch (token.type())
			{
				case TokenType::LeftBracket: // Index
					postfix = parseSubscriptExpression(*postfix);
					continue;

				case TokenType::LeftParenthesis: // FunctionAst call
					postfix = parseCallExpression(*postfix);
					continue;

				case TokenType::Dot: // MemberAst
					postfix = parseMemberAccessExpression(*postfix);
					continue;
				
				default:
					break;
			}

			break;
		}

		return postfix;
	}

	Optional<PrefixType> ParkaFileParser::parsePrefixType()
	{
		switch (token.type())
		{
			case TokenType::Ampersand:
				return PrefixType::Reference;

			case TokenType::Asterisk:
				return PrefixType::Dereference;

			case TokenType::Plus:
				return PrefixType::Positive;

			case TokenType::Minus:
				return PrefixType::Negative;

			case TokenType::BitwiseNot:
				return PrefixType::BitwiseNot;

			case TokenType::BooleanNot:
				return PrefixType::BooleanNot;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *ParkaFileParser::parsePrefixExpression()
	{
		auto start = Snippet(token);
		auto type = parsePrefixType();

		if (!type)
			return parsePostfixExpression();

		token.increment();

		auto *inner = parsePrefixExpression();

		if (inner == nullptr)
			return nullptr;

		auto snippet = start + inner->snippet();
		auto *syntax = new PrefixExpressionAst(snippet, *type, *inner);

		return syntax;
	}

	Optional<BinaryExpressionType> ParkaFileParser::getMultiplicativeType()
	{
		switch (token.type())
		{
			case TokenType::Modulus:
				return BinaryExpressionType::Modulus;

			case TokenType::Asterisk:
				return BinaryExpressionType::Multiply;

			case TokenType::Slash:
				return BinaryExpressionType::Divide;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *ParkaFileParser::parseMultiplicativeExpression()
	{
		auto *lhs = parsePrefixExpression();

		if (!lhs)
			return {};
		
		auto type = getMultiplicativeType();

		while (type)
		{
			token.increment();
			
			auto rhs = parsePrefixExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getMultiplicativeType();
		}

		return lhs;
	}

	Optional<BinaryExpressionType> ParkaFileParser::getAdditiveType()
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return BinaryExpressionType::Add;

			case TokenType::Minus:
				return BinaryExpressionType::Subtract;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *ParkaFileParser::parseAdditiveExpression()
	{
		auto *lhs = parseMultiplicativeExpression();

		if (!lhs)
			return {};
		
		auto type = getAdditiveType();

		while (type)
		{
			token.increment();

			auto rhs = parseMultiplicativeExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getAdditiveType();
		}

		return lhs;
	}

	Optional<BinaryExpressionType> ParkaFileParser::parseBitShiftType()
	{
		switch (token.type())
		{
			case TokenType::LeftBitShift:
				return BinaryExpressionType::LeftShift;

			case TokenType::RightBitShift:
				return BinaryExpressionType::RightShift;

			default:
				return {};
		}
	}

	ExpressionAst *ParkaFileParser::parseShiftExpression()
	{
		auto *lhs = parseAdditiveExpression();

		if (!lhs)
			return {};

		auto type = parseBitShiftType();

		while (type)
		{
			token.increment();

			auto rhs = parseAdditiveExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseBitShiftType();
		}

		return lhs;
	}

	Optional<BinaryExpressionType> ParkaFileParser::parseRelationalType()
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return BinaryExpressionType::GreaterThan;

			case TokenType::LessThan:
				return BinaryExpressionType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return BinaryExpressionType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return BinaryExpressionType::LessThanOrEqualTo;

			default:
				return {};
		}
	}
	
	ExpressionAst *ParkaFileParser::parseRelationalExpression()
	{
		auto *lhs = parseShiftExpression();

		if (!lhs)
			return {};

		auto type = parseRelationalType();

		while (type)
		{
			token.increment();

			auto rhs = parseShiftExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseRelationalType();
		}

		return lhs;
	}

	Optional<BinaryExpressionType> ParkaFileParser::getEqualityType()
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return BinaryExpressionType::Equals;

			case TokenType::NotEquals:
				return BinaryExpressionType::NotEquals;

			default:
				return {};
		}
	}

	ExpressionAst *ParkaFileParser::parseEqualityExpression()
	{
		auto *lhs = parseRelationalExpression();

		if (!lhs)
			return {};

		auto type = getEqualityType();

		while (type)
		{
			token.increment();

			auto rhs = parseRelationalExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getEqualityType();
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseAndExpression()
	{
		auto *lhs = parseEqualityExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = parseEqualityExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseAnd);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseXorExpression()
	{
		auto *lhs = parseBitwiseAndExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = parseBitwiseAndExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseXor);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseOrExpression()
	{
		auto *lhs = parseBitwiseXorExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = parseBitwiseXorExpression();

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseOr);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBooleanAndExpression()
	{
		auto *lhs = parseBitwiseOrExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = parseBitwiseOrExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanAnd);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBooleanOrExpression()
	{
		auto *lhs = parseBooleanAndExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = parseBooleanAndExpression();

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanOr);
		}


		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseConditionalExpression()
	{
		auto condition = parseBooleanOrExpression();
		auto keyword = KeywordAst::getKeywordType(token);

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = parseConditionalExpression();

		if (!trueCase)
			return {};

		keyword = KeywordAst::getKeywordType(token);

		if (keyword != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = parseConditionalExpression();

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionAst(*condition, *trueCase, *falseCase);

		return syntax;
	}

	Optional<BinaryExpressionType> ParkaFileParser::getAssignmentType()
	{
		switch (token.type())
		{
			case TokenType::Assign:
				return BinaryExpressionType::Assign;

			case TokenType::MultiplyAssign:
				return BinaryExpressionType::MultiplyAssign;

			case TokenType::DivideAssign:
				return BinaryExpressionType::DivideAssign;

			case TokenType::ModulusAssign:
				return BinaryExpressionType::ModulusAssign;

			case TokenType::AddAssign:
				return BinaryExpressionType::AddAssign;

			case TokenType::SubtractAssign:
				return BinaryExpressionType::SubtractAssign;

			case TokenType::LeftBitShiftAssign:
				return BinaryExpressionType::LeftShiftAssign;

			case TokenType::RightBitShiftAssign:
				return BinaryExpressionType::RightShiftAssign;

			case TokenType::BitwiseAndAssign:
				return BinaryExpressionType::BitwiseAndAssign;

			case TokenType::BitwiseOrAssign:
				return BinaryExpressionType::BitwiseOrAssign;

			case TokenType::BitwiseXorAssign:
				return BinaryExpressionType::BitwiseXorAssign;
			
			default:
				break;
		}

		return {};
	}

	ExpressionAst *ParkaFileParser::parseAssignmentExpression()
	{
		auto *lhs = parseConditionalExpression();

		if (!lhs)
			return {};

		auto type = getAssignmentType();

		if (!type)
			return lhs;

		token.increment();

		auto rhs = parseConditionalExpression();

		if (!rhs)
			return {};

		auto *expression = new BinaryExpressionAst(*lhs, *rhs, *type);

		return expression;
	}

	Optional<JumpType> ParkaFileParser::getJumpType()
	{
		auto keywordType = KeywordAst::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Return:
				return JumpType::Return;

			case KeywordType::Break:
				return JumpType::Break;

			case KeywordType::Continue:
				return JumpType::Continue;

			case KeywordType::Yield:
				return JumpType::Yield;

			default:
				log::parseError(token, "`return`, `break`, `continue` or `yield`");
				return {};
		}
	}

	StatementAst *ParkaFileParser::parseJumpStatement()
	{
		auto type = getJumpType();

		if (!type)
			return {};

		token.increment();

		ExpressionAst *value = nullptr;

		if (token.type() != TokenType::Semicolon)
		{
			switch (*type)
			{
				case JumpType::Continue:
					// TODO: Implement continuing on labels
					log::error(token, "Continue statements cannot have a value.");
					return {};
				
				case JumpType::Break:
					log::error(token, "Break statements cannot have a value.");
					return {};

				default:
					break;
			}
			
			value = parseExpression();

			if (!value)
				return {};
			
			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';' after jump statement");
				return {};
			}
		}

		token.increment();

		auto *syntax = new JumpStatementAst(token, *type, value);

		return syntax;
	}

	StatementAst *ParkaFileParser::parseExpressionStatement()
	{
		auto expression = parseExpression();

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';' after expression statement");
			return {};
		}

		auto snippet = expression->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new ExpressionStatementAst(snippet, *expression);

		return syntax;
	}

	StatementAst *ParkaFileParser::parseDeclarationStatement()
	{
		auto *variable = parseVariable();

		if (!variable)
			return nullptr;

		if (token.type() != TokenType::Assign)
		{
			log::parseError(token, "expected '=' after declaration");
			return nullptr;
		}

		token.increment();

		auto value = parseExpression();

		if (!value)
			return nullptr;

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';'", "DeclarationStatementAst statements need to be ended with a ';'.");
			return nullptr;
		}

		auto snippet = variable->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new DeclarationStatementAst(snippet, *variable, *value);

		return syntax;
	}

	StatementAst *ParkaFileParser::parseStatement()
	{
		auto keywordType = KeywordAst::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Var:
				return parseDeclarationStatement();

			case KeywordType::Return:
			case KeywordType::Break:
			case KeywordType::Continue:
			case KeywordType::Yield:
				return parseJumpStatement();

			default:
				break;
		}

		return parseExpressionStatement();
	}

	ParameterAst *ParkaFileParser::parseParameter()
	{
		auto first = Snippet(token);
		auto mutKeyword = KeywordAst::parseMut(token);
		auto isMutable = !!mutKeyword;
		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = parseTypeAnnotation();

		if (!annotation)
			return {};

		auto snippet = first + annotation->snippet();
		auto *syntax = new ParameterAst(snippet, *identifier, *annotation, isMutable);
		
		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseFunctionBody()
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = parseExpression();

			if (!body)
				return {};

			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';'", "Inline function bodies need to be ended with ';'.");
				return {};
			}

			token.increment();

			return body;
		}

		if (token.type() == TokenType::LeftBrace)
			return parseBlockExpression();
		
		log::parseError(token, "function body", "Functions require a body.");

		return {};
	}

	Optional<TypeAnnotationAst> ParkaFileParser::parseTypeAnnotation()
	{
		auto identifier = parseQualifiedIdentifier();

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationAst(identifier->snippet(), *identifier);

		return annotation;
	}

	VariableAst *ParkaFileParser::parseVariable()
	{
		// TODO: VariableAst mutability
		auto keyword = KeywordAst::parseVar(token);

		if (!keyword)
			return {};	
		
		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		auto end = identifier->snippet();

		Optional<TypeAnnotationAst> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = parseTypeAnnotation();

			if (!annotation)
				return {};

			end = annotation->snippet();
		}

		auto snippet = keyword->snippet() +  end;
		auto *syntax = new VariableAst(snippet, *identifier, false, std::move(annotation));

		return syntax;
	}

	Optional<PrototypeAst> ParkaFileParser::parsePrototype()
	{
		auto keyword = KeywordAst::parseFunction(token);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' after function name");
			return {};
		}

		token.increment();

		auto parameters = Array<ParameterAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto parameter = parseParameter();

				if (!parameter) // TODO: Attempt to fast forward to parameter
					return {};

				parameters.push(parameter);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				log::parseError(token, "')'", "Invalid tokens in parameter list");
				return {};
			}
		}

		auto end = Snippet(token);
		
		token.increment();

		Optional<TypeAnnotationAst> returnType;

		if (token.type() == TokenType::SingleArrow)
		{
			token.increment();

			returnType = parseTypeAnnotation();

			if (!returnType)
				return {};

			end = returnType->snippet();
		}

		auto snippet = keyword->snippet() + end;
		auto prototype = PrototypeAst(snippet, *identifier, std::move(parameters), std::move(returnType));

		return prototype;
	}

	FunctionAst *ParkaFileParser::parseFunction()
	{
		auto prototype = parsePrototype();

		if (!prototype)
			return {};

		auto body = parseFunctionBody();

		if (!body)
			return {};

		auto *syntax = new FunctionAst(*prototype, *body);

		return syntax;
	}

	bool ParkaFileParser::parsePublicity()
	{
		auto keywordType = KeywordAst::getKeywordType(token);

		if (keywordType == KeywordType::Public)
		{
			token.increment();
			return true;
		}

		if (keywordType == KeywordType::Private)
			token.increment();
		
		return false;
	}

	MemberAst *ParkaFileParser::parseMember()
	{
		auto first = Snippet(token);
		bool isPublic = parsePublicity();

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':''", "ValueType annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = parseTypeAnnotation();

		if (!annotation)
			return {};
			
		auto snippet = first + annotation->snippet();
		auto *syntax = new MemberAst(snippet, *identifier, *annotation, isPublic);

		return syntax;
	}

	StructAst *ParkaFileParser::parseStruct()
	{
		auto keyword = KeywordAst::parseStruct(token);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::LeftBrace)
		{
			// TODO: 
			log::parseError(token, "'{' before member list", "Bodyless structs are not allowed.");
			return {};
		}

		auto members = Array<MemberAst*>();

		token.increment();

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = parseMember();

				if (!member)
					return {};

				members.push(member);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightBrace)
			{
				log::parseError(token, "'}' after struct body");
				return {};
			}
		}

		auto snippet = keyword->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new StructAst(snippet, *identifier, std::move(members));

		return syntax;
	}

	ModuleAst ParkaFileParser::parse()
	{
		// TODO: Fast forwarding after encountering parse error to not stop after first failure
		auto functions = Array<FunctionAst*>();
		auto structs = Array<StructAst*>();

		while (true)
		{
			auto keywordType = KeywordAst::getKeywordType(token);

			switch (keywordType)
			{
				case KeywordType::Function:
				{
					auto *function = parseFunction();

					if (!function)
						break;

					functions.push(function);

					continue;
				}

				case KeywordType::StructAst:
				{
					auto *strct = parseStruct();

					if (!strct)
						break;

					structs.push(strct);

					continue;
				}

				default:
					break;
			}

			if (token.type() != TokenType::EndOfFile)
			{
				log::parseError(token, "type or function definition");
			}

			break;
		}

		auto mod = ModuleAst(String(_file.path()), std::move(functions), std::move(structs));

		return mod;
	}
}
