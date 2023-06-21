#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/Statement.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	StatementAst *DeclarationStatementAst::parse(Token& token)
	{
		auto *variable = VariableAst::parse(token);

		if (!variable)
			return nullptr;

		if (token.type() != TokenType::Assign)
		{
			log::parseError(token, "expected '=' after declaration");
			return nullptr;
		}

		token.increment();

		auto value = ExpressionAst::parse(token);

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

	// ir::StatementIr *DeclarationStatementAst::validate(SymbolTable& symbolTable)
	// {
	// 	auto *value = _value.validate(symbolTable);
	// 	auto *variable = _variable.validate(symbolTable, value);

	// 	if (!variable || !value)
	// 		return nullptr;

	// 	auto *context = new ir::DeclarationStatementIr(*variable, *value);

	// 	return context;
	// }
}
