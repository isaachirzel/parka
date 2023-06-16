#include "parka/ast/Prototype.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	Optional<PrototypeAst> PrototypeAst::parse(Token& token)
	{
		auto keyword = KeywordAst::parseFunction(token);

		if (!keyword)
			return {};

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' after function name");
			return {};
		}

		token.increment();

		auto parameters = Array<ParameterAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto parameter = ParameterAst::parse(token);

				if (!parameter) // TODO: Attempt to fast forward to parameter
					return {};

				parameters.push(parameter);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				log::parseError(token, "')'", "Invalid tokens in parameter list");
				return {};
			}
		}

		auto end = Snippet(token);
		
		token.increment();

		Optional<TypeAnnotationAst> returnType;

		if (token.type() == TokenType::SingleArrow)
		{
			token.increment();

			returnType = TypeAnnotationAst::parse(token);

			if (!returnType)
				return {};

			end = returnType->snippet();
		}

		auto snippet = keyword->snippet() + end;
		auto prototype = PrototypeAst(snippet, *identifier, std::move(parameters), std::move(returnType));

		return prototype;
	}

	static Optional<ir::ValueType> validateReturnType(Optional<TypeAnnotationAst>& syntax, SymbolTable& symbolTable)
	{
		if (!syntax)
			return ir::ValueType::voidType;

		return syntax->validate(symbolTable);
	}

	Optional<ir::PrototypeIr> PrototypeAst::validate(SymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = _parameters.length();
		auto parameters = Array<ir::ParameterIr*>(parameterCount);

		for (auto *parameterAst : _parameters)
		{
			auto *context = parameterAst->validate(symbolTable);

			if (context == nullptr)
			{
				success = false;
				continue;
			}

			parameters.push(context);
		}

		auto returnType = validateReturnType(_returnType, symbolTable);

		if (!returnType)
			success = false;

		if (!success)
			return {};

		auto context = ir::PrototypeIr(std::move(parameters), *returnType);

		return context;
	}

	std::ostream& operator<<(std::ostream& out, const PrototypeAst& syntax)
	{
		out << "function " << syntax._identifier << '(';

		bool isFirst = true;

		for (const auto *parameter : syntax._parameters)
		{
			if (!isFirst)
				out << ", ";

			out << *parameter;

			isFirst = false;
		}

		out << ")";

		return out;
	}
}
