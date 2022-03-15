#ifndef WARBLER_SEMANTICS_FUNCTION_HPP
#define WARBLER_SEMANTICS_FUNCTION_HPP

#include <warbler/semantics/function/function_signature.hpp>
#include <warbler/semantics/statement/block_statement.hpp>

namespace warbler::semantics
{
	class Function
	{
		String _symbol;
		FunctionSignature _signature;
		Optional<BlockStatement> _body;

	public:

		Function(String&& symbol, FunctionSignature&& signature, Optional<BlockStatement>&& body);

		const String& symbol() const { return _symbol; }
	};
}

#endif
