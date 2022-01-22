#ifndef WARBLER_SEMANTICS_SYMBOL_HPP
#define WARBLER_SEMANTICS_SYMBOL_HPP

namespace warbler::ast
{
	class Function;
}

namespace warbler::semantics
{
	class Symbol
	{
	private:

		ast::Function* _function;

	public:
	
		Symbol(ast::Function* function) :
		_function(function)
		{}

		ast::Function& function() { return *_function; }
		const ast::Function& function() const { return *_function; }
	};
}

#endif
