#include <warbler/util/file.hpp>

// local includes
#include <warbler/util/print.hpp>

// standard library
#include <cstdio>

namespace warbler
{
	Result<String> read_from_file(FILE *file)
	{
		if (fseek(file, 0, SEEK_END))
			return {};

		long size = ftell(file);

		if (size == -1)
			return {};

		if (fseek(file, 0, SEEK_SET))
			return {};
		
		String buffer;

		buffer.resize(size);

		size_t bytes_read = fread(&buffer[0], sizeof(char), size, file);

		buffer.resize(bytes_read);

		return buffer;
	}

	Result<String> read_file(const String& filepath)
	{
		FILE *file = fopen(filepath.c_str(), "r");
		
		if (!file)
		{
			print_error("failed to open file '" + filepath + "'");
			return {};
		}

		auto res =  read_from_file(file);

		fclose(file);

		if (!res)
		{
			print_error("failed to read file '" + filepath + "'");
			return {};
		}

		auto text = res.unwrap();

		if (text.empty())
		{
			print_error("file '" + filepath + "' was empty");
			return {};
		}

		return text;
	}
}
