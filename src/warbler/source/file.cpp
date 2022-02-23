#include <warbler/source/file.hpp>

#include <warbler/util/file.hpp>

#include <cassert>

namespace warbler::source
{
	File::File(String&& filename, String&& src, Array<usize>&& line_lengths) :
	_filename(filename),
	_src(src),
	_line_lengths(line_lengths)
	{}

	static Array<usize> get_line_lengths(const String& src)
	{
	}

	Result<File> File::read(const String& filepath)
	{
		auto res = read_file(filepath);

		if (!res)
			return {};

		String src(res.unwrap());
		Array<usize> line_lengths;
		auto estimated_line_count = src.size() / 80 + 1;
		usize last_start_of_line = 0;

		line_lengths.reserve(estimated_line_count);

		for (usize i = 0; i < src.size(); ++i)
		{
			if (src[i] == '\n')
			{
				auto line_length = i - last_start_of_line;

				line_lengths.push_back(line_length);
				last_start_of_line = i + 1;
			}
		}

		return File(String(filepath), std::move(src), std::move(line_lengths));
	}

	File File::from(const char *text)
	{
		assert(text != nullptr);

		String filename("<in-memory-file");
		String source(text);
		auto line_lengths = get_line_lengths(source);

		return File(std::move(filename), std::move(source), std::move(line_lengths));
	};
}