#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Statement.hpp"

namespace parka::ast
{
	ExpressionAst *BlockExpressionAst::parse(Token& token)
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
			auto *statement = StatementAst::parse(token);

			if (!statement)
				return {};

			statements.push(statement);
		}

		auto last = Token(token);

		token.increment();

		auto *syntax = new BlockExpressionAst(first + last, std::move(statements));

		return syntax;
	}

	ir::ExpressionIr *BlockExpressionAst::validate(SymbolTable& symbolTable)
	{
		bool success = false;
		auto statements = Array<ir::StatementIr*>(_statements.length());
		const auto& valueType = ir::ValueType::voidType;

		for (auto *syntax : _statements)
		{
			// TODO: Get and update valueType
			auto *context = syntax->validate(symbolTable);

			if (!context)
			{
				success = false;
				continue;
			}

			statements.push(context);
		}

		if (!success)
			return {};

		auto *context = new ir::BlockExpressionIr(std::move(statements), ir::ValueType(valueType));

		return context;
	}

	bool BlockExpressionAst::declare(Declarable& declarable)
	{
		return _parent->declare(declarable);
	}

	Resolvable *BlockExpressionAst::find(const Identifier& identifier)
	{
		return _parent->find(identifier);
	}

	Resolution *BlockExpressionAst::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent->resolve(identifier);
	}
}
