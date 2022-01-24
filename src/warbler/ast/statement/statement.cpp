#include <warbler/ast/statement/statement.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	Statement::Statement(ExpressionStatement&& expression) :
	_expression(expression),
	_type(STATEMENT_EXPRESSION)
	{}

	Statement::Statement(DeclarationStatement&& declaration) :
	_declaration(declaration),
	_type(STATEMENT_DECLARATION)
	{}

	Statement::Statement(IfStatement&& if_then) :
	_if_then(if_then),
	_type(STATEMENT_IF_THEN)
	{}

	// Statement::Statement(LoopStatement&& loop) :
	// _loop(loop),
	// _type(STATEMENT_LOOP)
	// {}

	// Statement::Statement(JumpStatement&& jump) :
	// _jump(jump),
	// _type(STATEMENT_JUMP)
	// {}

	Statement::Statement(Statement&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				new (&_expression) auto(std::move(other._expression));
				break;

			case STATEMENT_DECLARATION:
				new(&_declaration) auto(std::move(other._declaration));
				break;

			case STATEMENT_IF_THEN:
				new(&_if_then) auto(std::move(other._if_then));
				break;

			// case STATEMENT_LOOP:
			// 	_loop = std::move(other._loop);
			// 	break;

			// case STATEMENT_JUMP:
			// 	_jump = std::move(other._jump);
			// 	break;
		}
	}

	Statement::Statement(const Statement& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				new(&_expression) auto(other._expression);
				break;

			case STATEMENT_DECLARATION:
				new(&_declaration) auto(other._declaration);
				break;

			case STATEMENT_IF_THEN:
				new(&_if_then) auto(other._if_then);
				break;

			// case STATEMENT_LOOP:
			// 	_if_then = other._if_then;
			// 	break;

			// case STATEMENT_JUMP:
			// 	_jump = other._if_then;
			// 	break;
		}
	}

	Statement::~Statement()
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression.~ExpressionStatement();
				break;

			case STATEMENT_DECLARATION:
				_declaration.~DeclarationStatement();
				break;

			case STATEMENT_IF_THEN:
				_if_then.~IfStatement();
				break;

			// case STATEMENT_LOOP:
			// 	_loop.~LoopStatement();
			// 	break;

			// case STATEMENT_JUMP:
			// 	_jump.~JumpStatement();
			// 	break;
		}
	}

	Result<Statement> Statement::parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_VAR:				
			{
				auto res = DeclarationStatement::parse(iter);

				if (res.has_error())
					return res.error();

				return Statement(res.unwrap());
			}

			//case TOKEN_MATCH:
			case TOKEN_IF:
			{
				auto res = IfStatement::parse(iter);

				if (res.has_error())
					return res.error();

				return Statement(res.unwrap());
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

		if (res.has_error())
			return res.error();

		return Statement(res.unwrap());
	}

	Result<Array<Statement>> Statement::parse_compound(TokenIterator& iter)
	{
		iter += 1;

		Array<Statement> out;

		while (iter->type() != TOKEN_RBRACE)
		{
			auto res = Statement::parse(iter);

			if (res.has_error())
				return res.error();

			out.emplace_back(res.unwrap());
		}

		iter += 1;

		return out;
	}
	
	void Statement::print_tree(u32 depth) const
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression.print_tree(depth);
				break;

			case STATEMENT_DECLARATION:
				_declaration.print_tree(depth);
				break;

			case STATEMENT_IF_THEN:
				_if_then.print_tree(depth);
				break;

			// case STATEMENT_LOOP:
			// 	_loop.print_tree(depth);
			// 	break;

			// case STATEMENT_JUMP:
			// 	_jump.print_tree(depth);
			// 	break;
		}
	}

	Statement& Statement::operator=(Statement&& other)
	{
		new(this) auto(other);
		return *this;
	}

	Statement& Statement::operator=(const Statement& other)
	{
		new(this) auto(other);
		return *this;
	}
}
