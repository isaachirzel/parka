#ifndef PARKA_LOG_INDENT_HPP
#define PARKA_LOG_INDENT_HPP

#include "parka/util/Common.hpp"

namespace parka::log
{
	class Indent
	{
		long& _amount;

		static const int xIndex;

	public:

		Indent(std::ostream& stream);
		~Indent();

		friend std::ostream& operator<<(std::ostream& out, const Indent& indent);
	};
}

#endif
