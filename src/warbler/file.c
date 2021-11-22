#include <warbler/file.h>

// local includes
#include <warbler/error.h>

// standard library
#include <stdio.h>

const char *failed_to_open_file_str = "failed to open file";

char *read_file(const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	
	if (!file)
	{
		print_error(failed_to_open_file_str);		
		return NULL;
	}

	if (fseek(file, 0, SEEK_END);

}

std::string read_file(const std::string& filepath)
{
	std::ifstream file(filepath);

	if (!file.is_open())
		throw std::runtime_error("file '" + filepath + "' failed to open");

	file.seekg(0, std::ios::end);
	auto size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string out(size, 0);

	if (!file.read(&out[0], size))
		throw std::runtime_error("failed to read data from file: " + filepath);
	
	return out;
}
