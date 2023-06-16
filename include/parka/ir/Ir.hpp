#ifndef PARKA_IR_IR_HPP
#define PARKA_IR_IR_HPP

#include "parka/ir/Package.hpp"

namespace parka::ir
{
	class Ir
	{
		PackageIr& _globalPackage;
		
	public:

		Ir(PackageIr& globalPackage) :
		_globalPackage(globalPackage)
		{}
		Ir(Ir&&) = default;
		Ir(const Ir&) = default;

		const auto& globalPackage() const { return _globalPackage; }
	};
}

#endif
