#ifndef SYMBOL_H
#define SYMBOL_H

// local includes
#include <grackle/data/string.h>

// standard library
#include <string_view>

namespace grackle
{
	class Symbol
	{
	public: // sub-definitions

		enum Type
		{
			GLOBAL,
			FUNCTION,
			VARIABLE,
			ANONYMOUS
		};

	private: // members

		std::string_view _text;
		Type type;

	public:

		Symbol() = default;

	};
}

#endif
