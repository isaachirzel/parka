#ifndef PARKA_IR_TYPE_NAME_IR_HPP
#define PARKA_IR_TYPE_NAME_IR_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/util/String.hpp"

namespace parka::ir
{
	class InvalidTypeIr: public TypeIr
	{
		String _symbol;

	public:

		static InvalidTypeIr typeNameType;
		static InvalidTypeIr packageType;
		static InvalidTypeIr functionType;

	private:

		InvalidTypeIr(const char* name);
		InvalidTypeIr(InvalidTypeIr&&) = default;
		InvalidTypeIr(const InvalidTypeIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
	};
}

#endif
