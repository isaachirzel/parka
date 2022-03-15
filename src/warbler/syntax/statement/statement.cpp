#include <warbler/syntax/statement/statement.hpp>

// local headers
#include <warbler/syntax/statement/declaration_statement.hpp>
#include <warbler/syntax/statement/expression_statement.hpp>
#include <warbler/syntax/statement/if_statement.hpp>
#include <warbler/syntax/statement/assignment_statement.hpp>
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Statement::Statement(AssignmentStatement&& assignment) :
	_assignment(new AssignmentStatement(std::move(assignment))),
	_type(StatementType::Assignment)
	{}

	Statement::Statement(ExpressionStatement&& statement) :
	_expression(new ExpressionStatement(std::move(statement))),
	_type(StatementType::Expression)
	{}

	Statement::Statement(BlockStatement&& block) :
	_block(new BlockStatement(std::move(block))),
	_type(StatementType::Block)
	{}

	Statement::Statement(VariableStatement&& variable) :
	_variable(new VariableStatement(std::move(variable))),
	_type(StatementType::Variable)
	{}

	Statement::Statement(IfStatement&& if_statement) :
	_if(new IfStatement(std::move(if_statement))),
	_type(StatementType::If)
	{}

	Statement::Statement(Statement&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case StatementType::Assignment:
				_assignment = other._assignment;
				other._assignment = nullptr;
				break;

			case StatementType::Expression:
				_expression = other._expression;
				other._expression = nullptr;
				break;

			case StatementType::Block:
				_block = other._block;
				other._block = nullptr;
				break;

			case StatementType::Variable:
				_variable = other._variable;
				other._variable = nullptr;
				break;

			case StatementType::If:
				_if = other._if;
				other._if = nullptr;
				break;
		}
	}

	Statement::~Statement()
	{
		switch (_type)
		{
			case StatementType::Assignment:
				delete _assignment;
				break;
				
			case StatementType::Expression:
				delete _expression;
				break;
				
			case StatementType::Block:
				delete _block;
				break;
				
			case StatementType::Variable:
				delete _variable;
				break;
				
			case StatementType::If:
				delete _if;
				break;
			}
	}

	Result<Statement> Statement::parse(lexicon::Token& token)
	{
		switch (token.type())
		{
			case lexicon::TokenType::KeywordVar:
			{
				auto res = VariableStatement::parse(token);

				if (!res)
					return {};

				return Statement { res.unwrap() };
			}

			//case lexicon::TokenType::MATCH:
			case lexicon::TokenType::KeywordIf:
			{
				auto res = IfStatement::parse(token);

				if (!res)
					return {};

				return Statement { res.unwrap() };
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

		return Statement { res.unwrap() };
	}
}
