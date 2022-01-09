#include <warbler/file.h>

// local includes
#include <warbler/print.h>

// standard library
#include <stdio.h>
#include <stdlib.h>


static char *read_from_file(FILE *file, const char *filepath)
{
	if (fseek(file, 0, SEEK_END))
	{
		errorf("failed to iterate to end of file: ", filepath);
		return NULL;
	}

	long size = ftell(file);

	if (size == -1)
	{
		errorf("failed to get file size: %s", filepath);
		return NULL;
	}
	else if (size == 0)
	{
		errorf("file is empty: %s", filepath);
		return NULL;
	}

	if (fseek(file, 0, SEEK_SET))
	{
		errorf("failed to iterate to beginning of file: %s", filepath);
		return NULL;
	}

	char *buffer = malloc(size + 1);

	if (buffer == NULL)
	{
		errorf("failed to allocate buffer for file: %s", filepath);
		return NULL;
	}

	size_t bytes_read = fread(buffer, sizeof(char), size, file);

	if (bytes_read == 0)
	{
		free(buffer);
		errorf("failed to read data from file: %s", filepath);
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
		errorf("failed to open file: %s", filepath);
		return NULL;
	}

	char *out = read_from_file(file, filepath);

	fclose(file);

	return out;
}
