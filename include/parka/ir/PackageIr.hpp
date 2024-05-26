#ifndef PARKA_IR_PACKAGE_HPP
#define PARKA_IR_PACKAGE_HPP

#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/StructIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PackageIr: public LValueIr, public TypeIr
	{
		String _symbol;
		Array<PackageIr*> _packages;
		Array<FunctionIr*> _functions;
		Array<StructIr*> _structs;

	public:

		PackageIr(String&& symbol, Array<PackageIr*> packages, Array<FunctionIr*>&& functions, Array<StructIr*>&& structs):
			LValueIr(ResolvableType::Package),
			TypeIr(TypeCategory::Package),
			_symbol(std::move(symbol)),
			_packages(std::move(packages)),
			_functions(std::move(functions)),
			_structs(std::move(structs))
		{}
		PackageIr(PackageIr&&) = default;
		PackageIr(const PackageIr&) = delete;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return *this; }
		const auto& packages() const { return _packages; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};
}

#endif
