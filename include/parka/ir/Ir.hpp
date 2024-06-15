#ifndef PARKA_IR_IR_HPP
#define PARKA_IR_IR_HPP

#include "parka/ir/FunctionIr.hpp"

namespace parka::ir
{
	class Ir
	{
		String _name;
		Array<FunctionIr*> _functions;
		FunctionIr* _entryPoint;

	public:
		
		Ir(const String& name, Array<FunctionIr*>&& functions, FunctionIr *entryPoint):
			_name(name),
			_functions(std::move(functions)),
			_entryPoint(entryPoint)
		{}
		Ir(Ir&&) = default;
		Ir(const Ir&) = delete;

		const auto& name() const { return _name; }
		const auto& functions() const { return _functions; }
		bool hasEntryPoint() const { return !!_entryPoint; }
		const auto& entryPoint() const { assert(!!_entryPoint); return *_entryPoint; }
	};
}

#endif
