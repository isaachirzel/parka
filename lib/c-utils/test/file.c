#define _CRT_SECURE_NO_WARNINGS // windows deprecation warnings
#include <stdio.h>
#define HIRZEL_UTIL_FILE_I
#include <hirzel/util/file.h>
#define HIRZEL_UTIL_LIST_I
#include <hirzel/util/list.h>

#include <time.h>


int main()
{

	char** lines = hxfile_read_lines("./file.txt");

	int i = 0;
	const char** pos = (const char**)lines;
	while (*pos)
	{
		printf("%d: %s\n", i++, *pos++);
	}

	hxfile_free_lines(lines);
	lines = 0;
	return 0;
}
