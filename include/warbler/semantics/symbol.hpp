#ifndef WARBLER_SEMANTICS_SYMBOL_HPP
#define WARBLER_SEMANTICS_SYMBOL_HPP

#include <warbler/ast/function.hpp>

namespace warbler
{
	class Symbol
	{
	private:

		Function* _function;

	public:
	
		Symbol(Function* function) :
		_function(function)
		{}

		Function& function() { return *_function; }
		const Function& function() const { return *_function; }
	};
}

#endif
