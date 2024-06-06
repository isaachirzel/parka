#include "parka/ir/ParameterIr.hpp"

namespace parka::ir
{
	std::ostream& operator<<(std::ostream& out, const ParameterIr& parameter)	
	{
		out << parameter._symbol << ": " << parameter._type;

		return out;
	}
}