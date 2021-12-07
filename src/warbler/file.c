#include <warbler/file.h>

// local includes
#include <warbler/error.h>

// standard library
#include <stdio.h>
#include <stdlib.h>

char *file_error(const char *msg)
{
	print_error(msg);
	return NULL;
}

char *read_file(const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	
	if (!file)
		return file_error("failed to open file");

	if (fseek(file, 0, SEEK_END))
		return file_error("failed to iterate to end of file");

	long size = ftell(file);

	if (size == -1)
		return file_error("failed to get file size");
	else if (size == 0)
		return file_error("file is empty");

	if (fseek(file, 0, SEEK_SET))
		return file_error("failed to iterate to beginning of file");	

	char *out = malloc(sizeof(char) * (size + 1));

	if (!out)
		return file_error("failed to allocate buffer for file");

	out[size] = 0;

	size_t bytes_read = fread(out, sizeof(char), size, file);

	if (bytes_read == 0)
		return file_error("failed to read file");
	
	return out;
}
