#ifndef PARKA_IR_PACKAGE_HPP
#define PARKA_IR_PACKAGE_HPP

#include "parka/ir/Function.hpp"
#include "parka/ir/Struct.hpp"
#include "parka/symbol/Resolution.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PackageIr: public Resolution
	{
		String _symbol;
		Array<PackageIr*> _packages;
		Array<FunctionIr*> _functions;
		Array<StructIr*> _structs;

	public:

		PackageIr(String&& symbol, Array<PackageIr*> packages, Array<FunctionIr*>&& functions, Array<StructIr*>&& structs):
		Resolution(ResolvableType::Package),
		_symbol(std::move(symbol)),
		_packages(std::move(packages)),
		_functions(std::move(functions)),
		_structs(std::move(structs))
		{}
		PackageIr(PackageIr&&) = default;
		PackageIr(const PackageIr&) = delete;

		const String& symbol() const { return _symbol; }
		const auto& packages() const { return _packages; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};
}

#endif
