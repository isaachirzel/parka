#include "parka/util/ArenaStreamBuffer.hpp"
#include "parka/util/Common.hpp"
#include <cstring>
#include <stdexcept>
#include <streambuf>

namespace parka
{
	ArenaStreamBuffer::ArenaStreamBuffer(usize length):
	std::streambuf(),
	_buffer(length)
	{
		setp((char*)_buffer.begin(), (char*)_buffer.end());
	}

	std::streamsize ArenaStreamBuffer::xsputn(const char *src, std::streamsize n)
	{
		auto *dest = _buffer.allocate(n);

		std::memcpy(dest, src, n);

		return n;
	}

	int ArenaStreamBuffer::overflow(int)
	{
		throw std::runtime_error("ArenaStreamBuffer overflow");
	}
}
