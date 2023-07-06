#ifndef PARKA_IR_IR_HPP
#define PARKA_IR_IR_HPP

#include "parka/ir/Package.hpp"

namespace parka::ir
{
	class Ir
	{
		Array<FunctionIr*> _functions;
		FunctionIr *_entryPoint;

	public:
		
		Ir(Array<FunctionIr*>&& functions, FunctionIr *entryPoint):
		_functions(std::move(functions)),
		_entryPoint(entryPoint)
		{}
		Ir(Ir&&) = default;
		Ir(const Ir&) = delete;

		const auto& functions() const { return _functions; }
		const auto *entryPoint() const { return _entryPoint; }
	};
}

#endif
