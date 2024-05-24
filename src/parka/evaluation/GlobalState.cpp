#include "parka/evaluation/GlobalState.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	GlobalState::GlobalState():
		_intrinsicConversions(getIntrinsicConversions())
	{}

	Value& GlobalState::add(ir::LValueIr *, const ir::TypeIr&)
	{
		log::notImplemented(here());
		// auto insertion = _values.insert(key, Value(type));

		// if (!insertion)
		// 	log::fatal("Failed to insert value for $.", (void*)key);

		// return *insertion;
	}

	IntrinsicConversion GlobalState::getConversion(const ir::TypeIr& to, const ir::TypeIr& from) const
	{
		auto key = ConversionKey(to, from);
		auto* conversion = _intrinsicConversions.find(key);

		if (!conversion)
			log::fatal("Unable to find intrinsic conversion from `$` to `$`.", to, from);

		return *conversion;
	}
}
