#ifndef WARBLER_SYNTAX_FUNCTION_HPP
#define WARBLER_SYNTAX_FUNCTION_HPP

#include <warbler/util/array.hpp>

namespace warbler::syntax
{
	struct Parameter
	{

	};

	struct FunctionSignature
	{
		Array<Parameter> parameters;
		Type return_type;
	};

	struct Function
	{
		Identifier name;
		FunctionSignature signature;
		BlockStatement body;
	};
};

#endif
