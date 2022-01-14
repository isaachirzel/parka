#include <warbler/file.hpp>

// local includes
#include <warbler/print.hpp>

// standard library
#include <cstdio>

namespace warbler
{
	static char *read_from_file(FILE *file, const char *filepath)
	{
		if (fseek(file, 0, SEEK_END))
		{
			error_out() << "failed to iterate to end of file: " << filepath << std::endl;
			return NULL;
		}

		long size = ftell(file);

		if (size == -1)
		{
			error_out() << "failed to get file size: %s"<< filepath << std::endl;
			return NULL;
		}
		else if (size == 0)
		{
			error_out() << "file is empty: %s"<< filepath << std::endl;
			return NULL;
		}

		if (fseek(file, 0, SEEK_SET))
		{
			error_out() << "failed to iterate to beginning of file: %s" << filepath << std::endl;
			return NULL;
		}

		char *buffer = new char[size + 1];

		if (buffer == NULL)
		{
			error_out() << "failed to allocate buffer for file: %s" << filepath << std::endl;
			return NULL;
		}

		size_t bytes_read = fread(buffer, sizeof(char), size, file);

		if (bytes_read == 0)
		{
			delete buffer;
			error_out() << "failed to read data from file: %s" << filepath << std::endl;
			return NULL;
		}

		buffer[bytes_read] = '\0';

		return buffer;
	}

	char *read_file(const char *filepath)
	{
		FILE *file = fopen(filepath, "r");
		
		if (!file)
		{
			error_out() << "failed to open file: %s" << filepath << std::endl;
			return NULL;
		}

		char *out = read_from_file(file, filepath);

		fclose(file);

		return out;
	}
}
