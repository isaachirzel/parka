#include "parka/parser/ParkaParser.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	SyntaxTree parseSyntaxTree(const Project& project)
	{
	}

	PackageSyntax parsePackage(const Directory& directory, const String& name)
	{
	}

	ModuleSyntax parseModule(const File& file)
	{
	}

	Optional<StructSyntax> parseStruct(Token& token)
	{
	}

	Optional<MemberSyntax> parseMember(Token& token)
	{
	}

	Optional<TypeAnnotationSyntax> parseTypeAnnotation(Token& token)
	{
	}

	Optional<QualifiedIdentifier> parseQualifiedIdentifier(Token& token)
	{
	}

	Optional<Identifier> parseIdentifier(Token& token)
	{
	}

	Optional<FunctionSyntax> parseFunction(Token& token)
	{
	}

	Optional<PrototypeSyntax> parsePrototype(Token& token)
	{
	}

	Optional<ParameterSyntax> parseParameter(Token& token)
	{
		auto mutKeyword = KeywordSyntax::parseMut(token);
		auto isMutable = !!mutKeyword;
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};
		
		auto *syntax = new ParameterSyntax(*identifier, *annotation, isMutable);
		
		return syntax;
	}

	Optional<KeywordSyntax> parseKeyword(Token& token)
	{
	}

	Optional<VariableSyntax> parseVariable(Token& token)
	{
		// TODO: VariableSyntax mutability
		auto keyword = KeywordSyntax::parseVar(token);

		if (!keyword)
			return {};	
		
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		Optional<TypeAnnotationSyntax> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = TypeAnnotationSyntax::parse(token);

			if (!annotation)
				return {};
		}

		auto *syntax = new VariableSyntax(*identifier, false, std::move(annotation));

		return syntax;
	}

	ExpressionSyntax *parseExpression(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return BlockExpressionSyntax::parse(token);

		return AssignmentExpressionSyntax::parse(token);
	}

	static Optional<AdditiveType> getAdditiveType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return AdditiveType::Add;

			case TokenType::Minus:
				return AdditiveType::Subtract;

			default:
				break;
		}

		return {};
	}

	ExpressionSyntax *parseAdditiveExpression(Token& token)
	{
		auto *lhs = MultiplicativeExpressionSyntax::parse(token);

		if (!lhs)
			return {};
		
		auto type = getAdditiveType(token);

		while (type)
		{
			token.increment();

			auto rhs = MultiplicativeExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new AdditiveExpressionSyntax(*lhs, *rhs, *type);;
			type = getAdditiveType(token);
		}

		return lhs;
	}

	static Optional<AssignmentType> getAssignmentType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Assign:
				return AssignmentType::Become;

			case TokenType::MultiplyAssign:
				return AssignmentType::Multiply;

			case TokenType::DivideAssign:
				return AssignmentType::Divide;

			case TokenType::ModulusAssign:
				return AssignmentType::Modulus;

			case TokenType::AddAssign:
				return AssignmentType::Add;

			case TokenType::SubtractAssign:
				return AssignmentType::Subtract;

			case TokenType::LeftBitShiftAssign:
				return AssignmentType::LeftShift;

			case TokenType::RightBitShiftAssign:
				return AssignmentType::RightShift;

			case TokenType::BitwiseAndAssign:
				return AssignmentType::BitwiseAnd;

			case TokenType::BitwiseOrAssign:
				return AssignmentType::BitwiseOr;

			case TokenType::BitwiseXorAssign:
				return AssignmentType::BitwiseXor;
			
			default:
				return {};
		}
	}

	ExpressionSyntax *parseAssignmentExpression(Token& token)
	{
		auto *lhs = ConditionalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getAssignmentType(token);

		if (!type)
			return lhs;

		token.increment();

		auto rhs = ConditionalExpressionSyntax::parse(token);

		if (!rhs)
			return {};

		auto *expression = new AssignmentExpressionSyntax(*lhs, *rhs, *type);

		return expression;
	}

	ExpressionSyntax *parseBitwiseAndExpression(Token& token)
	{
		auto *lhs = EqualityExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = EqualityExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseAndExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionSyntax *parseBitwiseOrExpression(Token& token)
	{
		auto *lhs = BitwiseXorExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = BitwiseXorExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseOrExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionSyntax *parseBitwiseXorExpression(Token& token)
	{
		auto *lhs = BitwiseAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseXorExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionSyntax *parseBlockExpression(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			log::parseError(token, "'{' before block");

			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto statements = Array<StatementSyntax*>();

		while (token.type() != TokenType::RightBrace)
		{
			auto *statement = StatementSyntax::parse(token);

			if (!statement)
				return {};

			statements.push(statement);
		}

		token.increment();

		auto *syntax = new BlockExpressionSyntax(std::move(statements));

		return syntax;
	}

	ExpressionSyntax *parseBooleanAndExpression(Token& token)
	{
		auto *lhs = BitwiseOrExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = BitwiseOrExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BooleanAndExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionSyntax *parseBooleanOrExpression(Token& token)
	{
		auto *lhs = BooleanAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = BooleanAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BooleanOrExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionSyntax *parseCallExpression(Token& token)
	{
		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionSyntax*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto *argument = ExpressionSyntax::parse(token);

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

		token.increment();

		auto *syntax = new CallExpressionSyntax(primary, std::move(arguments));

		return syntax;
	}

	ExpressionSyntax *parseConditionalExpression(Token& token)
	{
		auto condition = BooleanOrExpressionSyntax::parse(token);
		auto keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = ConditionalExpressionSyntax::parse(token);

		if (!trueCase)
			return {};

		keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = ConditionalExpressionSyntax::parse(token);

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionSyntax(*condition, *trueCase, *falseCase);

		return syntax;
	}

	static Optional<EqualityType> getEqualityType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return EqualityType::Equals;

			case TokenType::NotEquals:
				return EqualityType::NotEquals;

			default:
				return {};
		}
	}

	ExpressionSyntax *parseEqualityExpression(Token& token)
	{
		auto *lhs = RelationalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getEqualityType(token);

		while (type)
		{
			token.increment();

			auto rhs = RelationalExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new EqualityExpressionSyntax(*lhs, *rhs, *type);
			type = getEqualityType(token);
		}

		return lhs;
	}

	ExpressionSyntax *parseIdentifierExpression(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto *syntax = new IdentifierExpressionSyntax(*identifier);

		return syntax;
	}

	ExpressionSyntax *parseIfExpression(Token& token)
	{
		log::notImplemented(here());
	}

	ExpressionSyntax *parseSubscriptExpression(Token& token)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			log::parseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = ExpressionSyntax::parse(token);

		if (!index)
			return {};

		auto *syntax = new SubscriptExpressionSyntax(primary, *index);

		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return syntax;
	}

	ExpressionSyntax *parseMemberAccessExpression(Token& token)
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

		auto *syntax = new MemberAccessExpressionSyntax(primary, token);

		token.increment();

		return syntax;
	}

	static Optional<MultiplicativeType> getMultiplicativeType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Modulus:
				return MultiplicativeType::Modulus;

			case TokenType::Asterisk:
				return MultiplicativeType::Multiply;

			case TokenType::Slash:
				return MultiplicativeType::Divide;

			default:
				return {};
		}
	}

	ExpressionSyntax *parseMultiplicativeExpression(Token& token)
	{
		auto *lhs = PrefixExpressionSyntax::parse(token);

		if (!lhs)
			return {};
		
		auto type = getMultiplicativeType(token);

		while (type)
		{
			token.increment();
			
			auto rhs = PrefixExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new MultiplicativeExpressionSyntax(*lhs, *rhs, *type);
			type = getMultiplicativeType(token);
		}

		return lhs;
	}

	static Optional<PrefixType> parsePrefixType(Token& token)
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
				return {};
		}
	}

	ExpressionSyntax *parsePrefixExpression(Token& token)
	{
		auto type = parsePrefixType(token);

		if (!type)
			return PostfixExpressionSyntax::parse(token);

		auto prefixToken = token;

		token.increment();

		auto *inner = PrefixExpressionSyntax::parse(token);
		auto *syntax = new PrefixExpressionSyntax(*type, *inner, prefixToken);

		return syntax;
	}

	static Optional<RelationalType> parseRelationalType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return RelationalType::GreaterThan;

			case TokenType::LessThan:
				return RelationalType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return RelationalType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return RelationalType::LessThanOrEqualTo;

			default:
				return {};
		}
	}
	
	ExpressionSyntax *parseRelationalExpression(Token& token)
	{
		auto *lhs = ShiftExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseRelationalType(token);

		while (type)
		{
			token.increment();

			auto rhs = ShiftExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new RelationalExpressionSyntax(*lhs, *rhs, *type);
			type = parseRelationalType(token);
		}

		return lhs;
	}

	static Optional<ShiftType> parseBitShiftType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::LeftBitShift:
				return ShiftType::Left;

			case TokenType::RightBitShift:
				return ShiftType::Right;

			default:
				return {};
		}
	}

	ExpressionSyntax *parseShiftExpression(Token& token)
	{
		auto *lhs = AdditiveExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseBitShiftType(token);

		while (type)
		{
			token.increment();

			auto rhs = AdditiveExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new ShiftExpressionSyntax(*lhs, *rhs, *type);
			type = parseBitShiftType(token);
		}

		return lhs;
	}

	static Optional<bool> parseBool(Token& token)
	{
		auto type = KeywordSyntax::getKeywordType(token);

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

	ExpressionSyntax *parseBoolLiteral(Token& token)
	{
		auto value = parseBool(token);

		if (!value)
			return {};

		auto *syntax = new BoolLiteralSyntax(token, *value);

		token.increment();

		return syntax;
	}

	static Optional<char> parseChar(Token& token)
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			log::parseError(token, "character");
			return {};
		}

		if (token.length() != 3)
		{
			log::error(token, "character literals may only contain 1 character", nullptr);
			return {};
		}

		auto character = token[0];

		return character;
	}

	ExpressionSyntax *parseCharLiteral(Token& token)
	{
		auto value = parseChar(token);

		if (!value)
			return {};

		auto *syntax = new CharLiteralSyntax(token, *value);

		token.increment();

		return syntax;
	}

	static Optional<f64> parseFloat(Token& token)
	{
		if (token.type() != TokenType::FloatLiteralSyntax)
		{
			log::parseError(token, "float");
			return {};
		}

		f64 parts[2] = { 0.0, 0.0 }; 
		usize partLens[2] = { 0, 0 };
		u32 partIndex = 0;

		for (const auto& c : token)
		{
			if (c == '.')
			{
				if (partIndex == 1)
					break;

				partIndex += 1;
				continue;
			}

			parts[partIndex] *= 10;
			parts[partIndex] += c - '0';
			partLens[partIndex] += 1;
		}

		auto offset = 1.0;

		for (usize i = 0; i < partLens[1]; ++i)
			offset *= 10.0;

		auto value = parts[0] + parts[1] / offset;

		return value;
	}

	ExpressionSyntax *parseFloatLiteral(Token& token)
	{
		auto value = parseFloat(token);

		if (!value)
			return {};

		auto *syntax = new FloatLiteralSyntax(token, value);

		token.increment();

		return syntax;
	}

	static Optional<u64> parseInteger(Token& token)
	{
		// TODO: Handle overflow

		if (token.type() != TokenType::IntegerLiteralSyntax)
		{
			log::parseError(token, "integer");
			return {};
		}

		u64 value = 0;

		for (usize i = 0; i < token.length(); ++i)
		{
			value *= 10;
			value += token[i] - '0';
		}
		
		return value;
	}

	static usize getMinimumIntegerBytes(u64 value)
	{
		usize bits = 0;

		while (value > 0)
		{
			value >>= 1;
			bits += 1;
		}

		return bits;
	}

	ExpressionSyntax *parseIntegerLiteral(Token& token)
	{
		auto value = parseInteger(token);

		if (!value)
			return {};

		auto bits = getMinimumIntegerBytes(value);
		auto *syntax = new IntegerLiteralSyntax(token, *value, bits);

		token.increment();

		return syntax;
	}

	ExpressionSyntax *parseStringLiteral(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			log::parseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralSyntax(token, token.text());

		token.increment();

		return syntax;
	}

	StatementSyntax *parseStatement(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Var:
				return DeclarationStatementSyntax::parse(token);

			case KeywordType::Return:
			case KeywordType::Break:
			case KeywordType::Continue:
			case KeywordType::Yield:
				return JumpStatementSyntax::parse(token);

			default:
				break;
		}

		return ExpressionStatementSyntax::parse(token);
	}

	StatementSyntax *parseDeclarationStatement(Token& token)
	{
		auto *variable = VariableSyntax::parse(token);

		if (!variable)
			return {};

		if (token.type() != TokenType::Assign)
		{
			log::parseError(token, "expected '=' after declaration");
			return {};
		}

		token.increment();

		auto value = ExpressionSyntax::parse(token);

		if (!value)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';'", "DeclarationStatementSyntax statements need to be ended with a ';'.");
			return {};
		}

		token.increment();

		auto *syntax = new DeclarationStatementSyntax(*variable, *value);

		return syntax;
	}

	StatementSyntax *parseExpressionStatement(Token& token)
	{
		auto expression = ExpressionSyntax::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';' after expression statement");
			return {};
		}

		token.increment();

		auto *syntax = new ExpressionStatementSyntax(*expression);

		return syntax;
	}

	static Optional<JumpType> getJumpType(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

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

	StatementSyntax *parseJumpStatement(Token& token)
	{
		auto type = getJumpType(token);

		if (!type)
			return {};

		// auto name = token;

		token.increment();

		ExpressionSyntax *value = nullptr;

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
			
			value = ExpressionSyntax::parse(token);

			if (!value)
				return {};
			
			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';' after jump statement");
				return {};
			}
		}

		token.increment();

		auto *syntax = new JumpStatementSyntax(token, *type, value);

		return syntax;
	}
}
