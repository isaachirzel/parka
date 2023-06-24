#ifndef PARKA_IR_IR_HPP
#define PARKA_IR_IR_HPP

#include "parka/ir/Package.hpp"

namespace parka::ir
{
	class Ir
	{
		Array<const FunctionIr*> _functions;

	public:
		
		Ir(Array<const FunctionIr*>&& functions):
		_functions(std::move(functions))
		{}
		Ir(Ir&&) = default;
		Ir(const Ir&) = delete;

		const auto& functions() const { return _functions; }
	};
}

#endif
