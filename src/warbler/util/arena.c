#include "warbler/util/memory.h"
#include "warbler/util/print.h"
#include <stdio.h>
#include <stdlib.h>
#include <warbler/util/arena.h>

#include <assert.h>

// TODO: Make this OS agnostic
#include <unistd.h>
#include <sys/mman.h>

static usize pageSize = 0;

usize getPageAlignedByteCount(usize bytes)
{
	usize difference = bytes % pageSize;

	if (difference > 0)
		bytes = (bytes - difference) + pageSize;

	return bytes;
}

Arena arenaCreate(usize minBytes)
{
	if (pageSize == 0)
		pageSize = getpagesize();

	usize bytes = getPageAlignedByteCount(minBytes);
	usize pageCount = bytes / pageSize;
	void *data = mmap(NULL, bytes, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (data == MAP_FAILED)
		exitWithErrorFmt("Failed to allocate Arena with size of %zu bytes.", bytes);

	Arena arena =
	{
		.data = data,
		.pageCount = pageCount
	};

	printSuccess("Successfully mapped Arena with %zu bytes.", bytes);

	return arena;
}

void arenaDestroy(Arena *arena)
{
	assert(arena != NULL);

	usize mappingLength = arena->pageCount * pageSize;

	munmap(arena->data, mappingLength);
}

void *arenaAllocate(Arena *arena, usize bytes)
{
	assert(arena != NULL);
	assert(arena->data != NULL);
	assert(arena->pageCount > 0);

	usize committedBytes = arena->committedPages * pageSize;
	usize requiredBytes = arena->bytesUsed + bytes;

	if (requiredBytes > committedBytes)
	{
		usize minBytesToCommit = requiredBytes - committedBytes;
		usize pagesToCommit = minBytesToCommit / pageSize;

		if (minBytesToCommit % pageSize > 0)
			pagesToCommit += 1;

		void *startOfPagesToCommit = (char*)arena->data + (arena->committedPages * pageSize);
		usize bytesToCommit = pagesToCommit * pageSize;
		int code = mprotect(startOfPagesToCommit, bytesToCommit, PROT_READ | PROT_WRITE);

		if (code == -1)
		{
			perror("Failed to commit pages");
			exitWithErrorFmt("Failed to commit %zu pages in Arena.", pagesToCommit);
		}

		printSuccess("Succesfully committed %zu pages in Arena.", pagesToCommit);
	}

	void *ptr = (char*)arena->data + arena->bytesUsed;

	arena->bytesUsed += bytes;


	return ptr;
}
