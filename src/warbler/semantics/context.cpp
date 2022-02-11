#include <warbler/semantics/context.hpp>

#include <cassert>

namespace warbler::semantics
{
// {
// 	String ModuleContext::qualified_scope() const
// 	{
// 		String out;
// 		usize size = 0;

// 		assert(!scope.empty());

// 		for (const auto& mod : scope)
// 			size += mod.size();

// 		size += (scope.size() - 1) * 2;	
// 		out.reserve(size);

// 		bool is_first = true;

// 		for (const auto& mod : scope)
// 		{
// 			out += mod;

// 			if (is_first)
// 			{
// 				is_first = false;
// 			}
// 			else
// 			{
// 				out += "::";
// 			}
// 		}

// 		return out;
// 	}

	// String ModueContext::qualified_scope(const String& name) const
	// {
	// 	String out;
	// 	usize size = 0;

	// 	for (const auto& mod : scope)
	// 		size += mod.size();

	// 	size += scope.size() * 2 + name.size();
	// 	out.reserve(size);

	// 	for (const auto& mod : scope)
	// 	{
	// 		out += mod;
	// 		out += "::";
	// 	}

	// 	out += name;

	// 	return out;
	// }
}
