#include <stdio.h>
#include <assert.h>

#include "intlist.h"
// #include "inttbl.h"

#include <hirzel/util/file.h>

void test_file()
{
}

void test_list()
{
	// testing list creation
	int_list_t *list = int_list_create();
	assert(list != NULL);
	assert(list->data == NULL);
	assert(list->len == 0);
	assert(int_list_is_empty(list));

	// pushing
	assert(int_list_push(list, 3));
	// 3
	assert(list->len == 1);
	assert(int_list_get(list, 0) == 3);
	assert(int_list_back(list) == 3);
	assert(int_list_front(list) == 3);
	assert(!int_list_is_empty(list));

	assert(int_list_push(list, 4));
	// 3 4
	assert(list->len == 2);
	assert(int_list_get(list, 1) == 4);
	assert(int_list_back(list) == 4);
	assert(int_list_front(list) == 3);
	assert(!int_list_is_empty(list));

	assert(int_list_pushf(list, 9));
	// 9 3 4
	assert(list->len == 3);
	assert(int_list_front(list) == 9);
	assert(int_list_back(list) == 4);

	// inserting

	assert(int_list_insert(list, 1, 12));
	// 9 12 3 4
	assert(int_list_front(list) == 9);
	assert(int_list_get(list, 1) == 12);
	assert(int_list_get(list, 2) == 3);
	assert(int_list_back(list) == 4);
	assert(list->len == 4);

	// popping

	assert(int_list_pop(list));
	// 9 12 3
	assert(int_list_back(list) == 3);
	assert(list->len == 3);
	assert(int_list_front(list) == 9);

	assert(int_list_popf(list));
	// 12 3
	assert(int_list_front(list) == 12);
	assert(int_list_back(list) == 3);
	assert(list->len == 2);

	// freeing data
	int_list_destroy(list);
}

// void test_table()
// {
// 	puts("Testing table");
// 	// CREATION
// 	puts("\tcreation...");
// 	int_tbl_t *table = hxtbl_int_create();
// 	assert(table != NULL);
// 	assert(table->data != NULL);
// 	assert(table->size == HXT_INIT_SIZE);
// 	assert(table->count == 0);

// 	const char *keys[] =
// 	{
// 		"abc", "bce", "cde", "def", "efg", "fgh", "hij", "ijk", "jkl", "klm",
// 		"lmn", "mno", "nop", "opq", "pqr", "qrs", "rst", "stu", "tuv", "uvw",
// 		"vwx", "wxy", "xyz", "yza", "zab"
// 	};

// 	size_t key_count = sizeof(keys) / sizeof(const char *);

// 	// SETTING
// 	puts("\tsetting...");
// 	for (size_t i = 0; i < key_count; ++i)
// 	{
// 		assert(int_tbl_set(table, keys[i], i * 2));
// 		assert(table->count == i + 1);
// 	}
// 	// assuring that the size has gone up appropriately
// 	assert(table->size > key_count * 2);

// 	// GETTING
// 	puts("\tgetting...");
// 	for (size_t i = 0; i < key_count; ++i)
// 	{
// 		assert(int_tbl_get(table, keys[i]) == i * 2);
// 	}
// 	assert(int_tbl_get(table, "key") == 0);
// 	assert(int_tbl_get(table, "hello") == 0);
	
// 	puts("\tcontains...");
// 	for (size_t i = 0; i < key_count; ++i)
// 	{
// 		assert(int_tbl_contains(table, keys[i]));
// 	}

// 	assert(!int_tbl_contains(table, "hello"));
// 	assert(!int_tbl_contains(table, "my man"));

// 	// DESTRUCTION
// 	hxtbl_int_destroy(table);
// 	puts("All tests passed\n");
// }

int main(void)
{
	//test_table();
	//print_primes();
	return 0;
}
