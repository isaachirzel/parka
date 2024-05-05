#ifndef PARKA_IR_DUMMY_TYPE_BASE_HPP
#define PARKA_IR_DUMMY_TYPE_BASE_HPP

#include "parka/ir/TypeBase.hpp"

namespace parka::ir
{
	class DummyTypeBase: public TypeBase
	{
		String _symbol;
		
	public:

		static DummyTypeBase packageTypeBase;
		static DummyTypeBase typeNameTypeBase;
		static DummyTypeBase functionTypeBase;

		DummyTypeBase(const char *name);

	public:

		const String& symbol() const { return _symbol; }
	};
}

#endif
