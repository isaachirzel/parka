#ifndef PARKA_IR_PACKAGE_HPP
#define PARKA_IR_PACKAGE_HPP

#include "parka/ir/Entity.hpp"
#include "parka/ir/Function.hpp"
#include "parka/ir/Struct.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PackageIr
	{
		String _symbol;
		Array<PackageIr*> _packages;
		Array<FunctionIr*> _functions;
		Array<StructIr*> _structs;

	public:

		PackageIr(String&& symbol, Array<PackageIr*> packages, Array<FunctionIr*>&& functions, Array<StructIr*>&& structs) :
		_symbol(std::move(symbol)),
		_packages(std::move(packages)),
		_functions(std::move(functions)),
		_structs(std::move(structs))
		{}
		PackageIr(PackageIr&&) = default;
		PackageIr(const PackageIr&) = delete;

		const String& symbol() const { return _symbol; }
		const ValueType *valueType() const;
		const auto& packages() const { return _packages; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};
}

#endif
