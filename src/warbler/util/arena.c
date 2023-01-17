#include <warbler/util/arena.h>

#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>

// TODO: Make this memory agnostic

static usize pageSize = 0;

void areaInit(void)
{
	pageSize = getpagesize();
}

usize getPageAlignedBytes(usize bytes)
{
	usize difference = bytes % pageSize;

	if (difference > 0)
		bytes = (bytes - difference) + pageSize;

	return bytes;
}

Arena arenaCreate(usize minBytes)
{
	assert(pageSize != 0);

	usize bytes = getPageAlignedBytes(minBytes);
	usize pageCount = bytes / pageSize;
	Arena arena =
	{
		.basePtr = mmap(NULL, bytes, PROT_NONE, MAP_ANONYMOUS, -1, 0),
		.pageCount = pageCount,
		.length = 0
	};


	return arena;
}

void arenaDestroy(Arena *arena)
{
	munmap(arena->basePtr, arena->pageCount * pageSize);
}

void *arenaAllocate(Arena *arena, usize bytes)
{
	usize usedBytesInPage = arena->length % pageSize;
	usize remainingBytesInPage = pageSize - usedBytesInPage;

	if (bytes > remainingBytesInPage)
	{
		usize bytesToAllocate = bytes - remainingBytesInPage;
		usize pagesToAllocate = bytesToAllocate / pageSize;

		if (bytesToAllocate % pageSize > 0)
			pagesToAllocate += 1;

		void *startOfNewAllocation = (char*)arena->basePtr + (arena->pageCount * pageSize);

		mprotect(startOfNewAllocation, pagesToAllocate, PROT_READ | PROT_WRITE);
	}

	void *ptr = (char*)arena->basePtr + arena->length;

	return ptr;
}
