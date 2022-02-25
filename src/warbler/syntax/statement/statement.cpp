#include <warbler/syntax/statement/statement.hpp>

// local headers
#include <warbler/syntax/statement/declaration_statement.hpp>
#include <warbler/syntax/statement/expression_statement.hpp>
#include <warbler/syntax/statement/if_statement.hpp>
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Result<Ptr<Statement>> Statement::parse(lexicon::TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_VAR:
			{
				auto res = DeclarationStatement::parse(iter);

				if (!res)
					return {};

				return Ptr<Statement> { new DeclarationStatement { res.unwrap() } };
			}

			//case TOKEN_MATCH:
			case TOKEN_IF:
			{
				auto res = IfStatement::parse(iter);

				if (!res)
					return {};

				return Ptr<Statement> { new IfStatement { res.unwrap() } };
			}

			// case TOKEN_LOOP:
			// case TOKEN_WHILE:
			// case TOKEN_FOR:
			// 	return parse_statement<LoopStatement>(iter);

			// case TOKEN_CONTINUE:
			// case TOKEN_BREAK:
			// case TOKEN_RETURN:
			// 	return parse_statement<JumpStatement>(iter);

			default:
				break;
		}

		auto res = ExpressionStatement::parse(iter);

		if (!res)
			return {};

		return Ptr<Statement> { new ExpressionStatement { res.unwrap() } };
	}
}
