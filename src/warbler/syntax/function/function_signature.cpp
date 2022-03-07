#include <warbler/syntax/function/function_signature.hpp>

namespace warbler::syntax
{
	FunctionSignature::FunctionSignature(Array<Parameter>&& parameters, Optional<Type>&& return_type) :
	_parameters(std::move(parameters)),
	_return_type(std::move(return_type))
	{}

	Result<FunctionSignature> FunctionSignature::parse(lexicon::Token& token)
	{
		auto parameters = Parameter::parse_list(token);

		if (!parameters)
			return {};

		Optional<Type> type;

		if (token.type() == lexicon::TokenType::Colon)
		{
			auto type_res = Type::parse(token.next());

			if (!type_res)
				return {};

			type = type_res.unwrap();
		}

		return FunctionSignature(parameters.unwrap(), std::move(type));
	}
}
