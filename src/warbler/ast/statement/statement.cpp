#include <warbler/ast/statement/statement.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
	Statement::Statement(ExpressionStatement&& expression) :
	_expression(expression),
	_type(STATEMENT_EXPRESSION)
	{}

	Statement::Statement(DeclarationStatement&& declaration) :
	_declaration(declaration),
	_type(STATEMENT_DECLARATION)
	{}

	Statement::Statement(SelectionStatement&& selection) :
	_selection(selection),
	_type(STATEMENT_SELECTION)
	{}

	Statement::Statement(LoopStatement&& loop) :
	_loop(loop),
	_type(STATEMENT_LOOP)
	{}

	Statement::Statement(JumpStatement&& jump) :
	_jump(jump),
	_type(STATEMENT_JUMP)
	{}

	Statement::Statement(Statement&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression = std::move(other._expression);
				break;

			case STATEMENT_DECLARATION:
				_declaration = std::move(other._declaration);
				break;

			case STATEMENT_SELECTION:
				_selection = std::move(other._selection);
				break;

			case STATEMENT_LOOP:
				_loop = std::move(other._loop);
				break;

			case STATEMENT_JUMP:
				_jump = std::move(other._jump);
				break;
		}
	}

	Statement::Statement(const Statement& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression = other._expression;
				break;

			case STATEMENT_DECLARATION:
				_declaration = other._declaration;
				break;

			case STATEMENT_SELECTION:
				_selection = other._selection;
				break;

			case STATEMENT_LOOP:
				_loop = other._loop;
				break;

			case STATEMENT_JUMP:
				_jump = other._jump;
				break;
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

			case STATEMENT_SELECTION:
				_selection.~SelectionStatement();
				break;

			case STATEMENT_LOOP:
				_loop.~LoopStatement();
				break;

			case STATEMENT_JUMP:
				_jump.~JumpStatement();
				break;
		}
	}

	template<typename T>
	static Result<Statement> parse_statement(TokenIterator& iter)
	{
		auto res = T::parse(iter);

		if (res.has_error())
			return res.error();

		if (iter->type() != TOKEN_SEMICOLON)
		{
			error_out(iter) << "expected ';' but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		iter += 1;

		return Statement(res.unwrap());
	}

	Result<Statement> Statement::parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_VAR:
				return parse_statement<DeclarationStatement>(iter);

			case TOKEN_MATCH:
			case TOKEN_IF:
				return parse_statement<SelectionStatement>(iter);

			case TOKEN_LOOP:
			case TOKEN_WHILE:
			case TOKEN_FOR:
				return parse_statement<LoopStatement>(iter);

			case TOKEN_CONTINUE:
			case TOKEN_BREAK:
			case TOKEN_RETURN:
				return parse_statement<JumpStatement>(iter);

			default:
				return parse_statement<ExpressionStatement>(iter);
		}
	}

	Result<std::vector<Statement>> Statement::parse_compound(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LBRACE)
		{
			error_out(iter) << "expected '{' but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		std::vector<Statement> out;

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

			case STATEMENT_SELECTION:
				_selection.print_tree(depth);
				break;

			case STATEMENT_LOOP:
				_loop.print_tree(depth);
				break;

			case STATEMENT_JUMP:
				_jump.print_tree(depth);
				break;
		}
	}

	Statement& Statement::operator=(Statement&& other)
	{
		_type = other._type;

		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression = std::move(other._expression);
				break;

			case STATEMENT_DECLARATION:
				_declaration = std::move(other._declaration);
				break;

			case STATEMENT_SELECTION:
				_selection = std::move(other._selection);
				break;

			case STATEMENT_LOOP:
				_loop = std::move(other._loop);
				break;

			case STATEMENT_JUMP:
				_jump = std::move(other._jump);
				break;
		}

		return *this;
	}

	#pragma message("figure out if destruction of statement will cause double free or not")

	Statement& Statement::operator=(const Statement& other)
	{
		_type = other._type;

		switch (_type)
		{
			case STATEMENT_EXPRESSION:
				_expression = other._expression;
				break;

			case STATEMENT_DECLARATION:
				_declaration = other._declaration;
				break;

			case STATEMENT_SELECTION:
				_selection = other._selection;
				break;

			case STATEMENT_LOOP:
				_loop = other._loop;
				break;

			case STATEMENT_JUMP:
				_jump = other._jump;
				break;
		}

		return *this;
	}

}
