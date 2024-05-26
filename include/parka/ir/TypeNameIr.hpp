#ifndef PARKA_IR_TYPE_NAME_IR_HPP
#define PARKA_IR_TYPE_NAME_IR_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/util/String.hpp"

namespace parka::ir
{
	class TypeNameIr: public TypeIr
	{
		String _symbol;

	public:

		static TypeNameIr instance;

	private:

		TypeNameIr();
		TypeNameIr(TypeNameIr&&) = default;
		TypeNameIr(const TypeNameIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
	};
}

#endif
