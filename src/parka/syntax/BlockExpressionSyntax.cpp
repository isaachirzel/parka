#include "parka/syntax/BlockExpressionSyntax.hpp"
#include "parka/context/BlockExpressionContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/StatementSyntax.hpp"

namespace parka
{
	BlockExpressionSyntax::BlockExpressionSyntax(Array<StatementSyntax*>&& statements) :
	_statements(std::move(statements)),
	_parent(nullptr),
	_symbols(nullptr),
	_baseIndex(0)
	{}

	ExpressionSyntax *BlockExpressionSyntax::parse(Token& token)
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

	ExpressionContext *BlockExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		bool success = false;
		auto statements = Array<StatementContext*>(_statements.length());

		for (auto *syntax : _statements)
		{
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

		auto *context = new BlockExpressionContext(std::move(statements));

		return context;
	}

	bool BlockExpressionSyntax::declareEntity(EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();

		for (const auto *entry : *_symbols)
		{
			if (identifier == entry->identifier())
			{
				log::error("Declaration of `$` shadows a previously declared $.", identifier, entry->entityType());
				// TODO: Show previous declaration
				// TODO: Maybe insert anyway?
				return false;
			}
		}

		_symbols->push(&entity);

		return true;
	}

	const EntityContext *BlockExpressionSyntax::resolve(const Identifier& identifier)
	{
		return _parent->resolve(identifier);
	}

	const EntityContext *BlockExpressionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent->resolve(identifier);
	}
}
