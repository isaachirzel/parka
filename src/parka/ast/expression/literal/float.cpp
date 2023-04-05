#include "parka/ast/expression/literal/float.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<f64> parseFloat(Token& token)
{
	if (token.type() != TokenType::FloatLiteral)
	{
		printParseError(token, "float");
		return {};
	}

	f64 parts[2] = { 0.0, 0.0 }; 
	usize partLens[2] = { 0, 0 };
	u32 partIndex = 0;

	for (const auto& c : token)
	{
		if (c == '.')
		{
			if (partIndex == 1)
				break;

			partIndex += 1;
			continue;
		}

		parts[partIndex] *= 10;
		parts[partIndex] += c - '0';
		partLens[partIndex] += 1;
	}

	auto offset = 1.0;

	for (usize i = 0; i < partLens[1]; ++i)
		offset *= 10.0;

	auto value = parts[0] + parts[1] / offset;

	return value;
	
}

Optional<ExpressionId> FloatLiteral::parse(Token& token)
{
	auto value = parseFloat(token);

	if (!value)
		return {};

	auto expression = FloatLiteral(token, value);
	auto id = NodeBank::add(std::move(expression));

	token.increment();

	return id;
}


bool FloatLiteral::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> FloatLiteral::getType() const
{
	exitNotImplemented(here());
}

