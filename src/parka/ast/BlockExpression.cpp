#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Statement.hpp"

namespace parka
{
	BlockExpressionSyntax::BlockExpressionSyntax(Array<StatementSyntax*>&& statements) :
	_statements(std::move(statements)),
	_parent(nullptr),
	_symbols(nullptr),
	_baseIndex(0)
	{}

	BlockExpressionContext::BlockExpressionContext(Array<StatementContext*>&& statements, ValueType&& valueType) :
	_statements(std::move(statements)),
	_valueType(std::move(valueType))
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

	bool BlockExpressionSyntax::declareEntity(EntitySyntax& entity)
	{
		const auto& name = entity.name();

		for (const auto *entry : *_symbols)
		{
			if (name == entry->name())
			{
				log::error("Declaration of `$` shadows a previously declared $.", name, entry->entityType());
				// TODO: Show previous declaration
				// TODO: Maybe insert anyway?
				return false;
			}
		}

		_symbols->push(&entity);

		return true;
	}

	bool BlockExpressionSyntax::declare(EntitySyntax& entity)
	{
		return _parent->declare(entity);
	}

	EntitySyntax *BlockExpressionSyntax::resolve(const Identifier& identifier)
	{
		return _parent->resolve(identifier);
	}

	EntitySyntax *BlockExpressionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent->resolve(identifier);
	}
}
