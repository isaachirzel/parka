#ifndef PARKA_LOG_CODE_SNIPPET_HPP
#define PARKA_LOG_CODE_SNIPPET_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class CodeSnippet
	{
		u8 _type;
		u8 _index;
		u8 _length;

	public:

		CodeSnippet(u8 index, u8 length);
	};
}

#endif
