#include <warbler/syntax/statement/statement.hpp>

// local headers
#include <warbler/syntax/statement/declaration_statement.hpp>
#include <warbler/syntax/statement/expression_statement.hpp>
#include <warbler/syntax/statement/if_statement.hpp>
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Result<Ptr<Statement>> Statement::parse(lexicon::Token& token)
	{
		switch (token.type())
		{
			case lexicon::TokenType::KeywordVar:
			{
				auto res = DeclarationStatement::parse(token.next());

				if (!res)
					return {};

				return Ptr<Statement> { new DeclarationStatement { res.unwrap() } };
			}

			//case lexicon::TokenType::MATCH:
			case lexicon::TokenType::KeywordIf:
			{
				auto res = IfStatement::parse(token.next());

				if (!res)
					return {};

				return Ptr<Statement> { new IfStatement { res.unwrap() } };
			}

			// case lexicon::TokenType::LOOP:
			// case lexicon::TokenType::WHILE:
			// case lexicon::TokenType::FOR:
			// 	return parse_statement<LoopStatement>(iter);

			// case lexicon::TokenType::CONTINUE:
			// case lexicon::TokenType::BREAK:
			// case lexicon::TokenType::RETURN:
			// 	return parse_statement<JumpStatement>(iter);

			default:
				break;
		}

		auto res = ExpressionStatement::parse(token.next());

		if (!res)
			return {};

		return Ptr<Statement> { new ExpressionStatement { res.unwrap() } };
	}
}
