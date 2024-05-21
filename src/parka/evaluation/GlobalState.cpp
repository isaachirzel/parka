#include "parka/evaluation/GlobalState.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	Value& GlobalState::add(ir::LValueIr *, const ir::TypeIr&)
	{
		log::notImplemented(here());
		// auto insertion = _values.insert(key, Value(type));

		// if (!insertion)
		// 	log::fatal("Failed to insert value for $.", (void*)key);

		// return *insertion;
	}
}
