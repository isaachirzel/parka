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
			print_error("Failed to open file '" + filepath + "' for reading.");
			return {};
		}

		auto res =  read_from_file(file);

		fclose(file);

		if (!res)
		{
			print_error("Failed to read file '" + filepath + "'.");
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

	bool write_file(const String& filepath, const String& content)
	{
		FILE * file = fopen(filepath.c_str(), "w");

		if (!file)
		{
			print_error("Failed to open file '" + filepath + "' for writing.");
			return false;
		}

		auto bytes_written = fwrite(content.c_str(), sizeof(char), content.size(), file);

		fclose(file);

		if (bytes_written != content.size())
		{
			print_error("Failed to write content to file '" + filepath + "'.");
			return false;
		}

		return true;
	}
}
