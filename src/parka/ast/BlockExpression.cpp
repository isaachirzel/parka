#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Statement.hpp"

namespace parka
{
	ExpressionSyntax *BlockExpressionSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			log::parseError(token, "'{' before block");

			return {};
		}

		auto first = Token(token);

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

		auto last = Token(token);

		token.increment();

		auto *syntax = new BlockExpressionSyntax(first + last, std::move(statements));

		return syntax;
	}

	ExpressionContext *BlockExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		bool success = false;
		auto statements = Array<StatementContext*>(_statements.length());
		const auto& valueType = ValueType::voidType;

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

		auto *context = new BlockExpressionContext(std::move(statements), ValueType(valueType));

		return context;
	}

	bool BlockExpressionSyntax::declare(EntitySyntax& entity)
	{
		return _parent->declare(entity);
	}

	EntityEntry *BlockExpressionSyntax::find(const Identifier& identifier)
	{
		return _parent->find(identifier);
	}

	EntityContext *BlockExpressionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent->resolve(identifier);
	}
}
