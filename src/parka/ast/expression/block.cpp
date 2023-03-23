#include "parka/ast/expression/block.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/parser.hpp"

#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<Box<Expression>> Block::parse(Token& token)
{
	if (token.type() != TokenType::LeftBrace)
	{
		printParseError(token, "'{' before block");

		return {};
	}

	token.increment();

	// TODO: Add initial capacity
	auto statements = Array<Box<Statement>>();

	while (token.type() != TokenType::RightBrace)
	{
		if (token.type() == TokenType::EndOfFile)
		{
			printParseError(token, "'}' after block");
			return {};
		}

		auto statement = Statement::parse(token);

		if (!statement)
			return {};

		statements.emplace_back(statement.unwrap());
	}

	token.increment();

	auto block = new Block(std::move(statements));
	auto result = Box<Expression>(block);

	return result;
}

bool Block::validate(SymbolTable& symbols)
{
	symbols.pushBlock(*this);

	bool success = true;

	for (auto& statement : _statements)
	{
		if (!statement->validate(symbols))
			success = false;
	}

	symbols.popBlock();

	return success;
}

Optional<Type> Block::getType(const SymbolTable& symbols, Ref<Type> expected) const
{
	if (_returnType)
		return Type(_returnType.value());

	return Type(voidType);
}
