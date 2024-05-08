#ifndef PARKA_IR_DUMMY_TYPE_BASE_HPP
#define PARKA_IR_DUMMY_TYPE_BASE_HPP

#include "parka/ir/TypeBase.hpp"

namespace parka::ir
{
	class DummyTypeBase: public TypeBase
	{
		String _symbol;
		
	public:

		static const DummyTypeBase packageTypeBase;
		static const DummyTypeBase typeNameTypeBase;
		static const DummyTypeBase functionTypeBase;
		static const DummyTypeBase integerTypeBase;
		static const DummyTypeBase floatTypeBase;

		DummyTypeBase(const char *name);

	public:

		const String& symbol() const { return _symbol; }
	};
}

#endif
