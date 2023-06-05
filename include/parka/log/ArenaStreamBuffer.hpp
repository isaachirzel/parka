#ifndef PARKA_LOG_ARENA_STREAM_BUFFER_HPP
#define PARKA_LOG_ARENA_STREAM_BUFFER_HPP

#include "parka/util/Arena.hpp"

namespace parka
{
	class ArenaStreamBuffer : public std::streambuf
	{
		Arena _buffer;

	protected:

		std::streamsize xsputn(const char *s, std::streamsize n) override;
		int overflow(int ch) override;

	public:

		ArenaStreamBuffer(usize length);
	};
}

#endif
