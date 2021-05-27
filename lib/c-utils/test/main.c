#include <stdio.h>
#include <assert.h>

#include "intlist.h"
#include "inttbl.h"

#include <hirzel/util/file.h>

void test_file()
{
}

void test_list()
{
	puts("Testing list");
	// testing list creation
	puts("\tcreation...");
	int_list_t *list = int_list_create();
	assert(list != NULL);
	assert(list->data == NULL);
	assert(list->len == 0);
	assert(int_list_empty(list));

	// pushing
	puts("\tpushing...");
	assert(int_list_push(list, 3));
	// 3
	assert(list->len == 1);
	assert(int_list_get(list, 0) == 3);
	assert(int_list_back(list) == 3);
	assert(int_list_front(list) == 3);
	assert(!int_list_empty(list));

	assert(int_list_push(list, 4));
	// 3 4
	assert(list->len == 2);
	assert(int_list_get(list, 1) == 4);
	assert(int_list_back(list) == 4);
	assert(int_list_front(list) == 3);
	assert(!int_list_empty(list));

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
	puts("\tpopping...");
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
	puts("All tests passed\n");
}

void test_table()
{
	puts("Testing table");
	// CREATION
	puts("\tcreation...");
	int_tbl_t *table = int_tbl_create();
	assert(table != NULL);
	assert(table->data != NULL);
	assert(table->size_idx == 0);
	assert(table->count == 0);
	assert(int_tbl_empty(table));

	const char *keys[] =
	{
		"abc", "bce", "cde", "def", "efg", "fgh", "hij", "ijk", "jkl", "klm",
		"lmn", "mno", "nop", "opq", "pqr", "qrs", "rst", "stu", "tuv", "uvw",
		"vwx", "wxy", "xyz", "yza", "zab"
	};

	const char *non_keys[] =
	{
		"this", "array", "of", "keys", "does", "not", "get", "inserted", "into",
		"the", "table"
	};

	size_t non_key_count = sizeof(non_keys) / sizeof(const char *);

	size_t key_count = sizeof(keys) / sizeof(const char *);

	// SETTING
	puts("\tsetting...");
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_set(table, keys[i], i * 2));
		assert(table->count == i + 1);
	}

	// storing table size after setting
	size_t table_size_idx = table->size_idx;
	size_t table_count = table->count;
	// assuring that the size has gone up appropriately
	assert(int_tbl_size(table) > key_count * 2);
	assert(!int_tbl_empty(table));

	// GETTING
	puts("\tgetting & contains...");
	// testing keys that have been inserted
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_get(table, keys[i]) == (int)i * 2);
		assert(*int_tbl_getref(table, keys[i]) == (int)i * 2);
		assert(int_tbl_contains(table, keys[i]));
	}
	

	// testing keys that haven't been inserted
	for (size_t i = 0; i < non_key_count; ++i)
	{
		assert(int_tbl_get(table, non_keys[i]) == 0);
		assert(int_tbl_getref(table, non_keys[i]) == NULL);
		assert(!int_tbl_contains(table, non_keys[i]));
	}
	
	assert(table->size_idx == table_size_idx);
	assert(table->count == table_count);

	// CLEARING
	puts("\tclearing...");
	int_tbl_clear(table);
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_get(table, keys[i]) == 0);
		assert(int_tbl_getref(table, keys[i]) == NULL);
		assert(!int_tbl_contains(table, keys[i]));
	}

	assert(table->size_idx == table_size_idx);
	assert(table->count == 0);
	assert(int_tbl_empty(table));

	// REINSERTING 
	puts("\treinserting...");
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_set(table, keys[i], (int)i * 2));
		assert(table->count == i + 1);
		struct int_tbl_node *node = int_tbl_getnode(table, keys[i], strlen(keys[i]));
		assert(node != NULL);
		assert(!strcmp(node->key, keys[i]));
	}

	assert(table->size_idx == table_size_idx);
	assert(table->count == table_count);

	// ERASING
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_erase(table, keys[i]));
	}

	for (size_t i = 0; i < non_key_count; ++i)
	{
		assert(!int_tbl_erase(table, non_keys[i]));
	}

	assert(int_tbl_empty(table));
	assert(table->size_idx == table_size_idx);

	// getting and contains
	for (size_t i = 0; i < key_count; ++i)
	{
		assert(int_tbl_get(table, keys[i]) == 0);
		assert(int_tbl_getref(table, keys[i]) == NULL);
		assert(!int_tbl_contains(table, keys[i]));
	}

	// 6 of them so it won't shrink to init size
	const char *keys2[] = { "a", "b", "c", "d", "e", "f" };
	size_t key_count2 = sizeof(keys2) / sizeof(const char *);

	for (size_t i = 0; i < key_count2; ++i)
	{
		assert(int_tbl_set(table, keys2[i], (i + 1) * 10));
	}

	// swapping a and b
	assert(int_tbl_get(table, "a") == 10);
	assert(int_tbl_get(table, "b") == 20);
	assert(int_tbl_swap(table, "a", "b"));
	assert(int_tbl_get(table, "a") == 20);
	assert(int_tbl_get(table, "b") == 10);

	// swapping a and f
	assert(int_tbl_get(table, "f") == 60);
	assert(int_tbl_swap(table, "a", "f"));
	assert(int_tbl_get(table, "a") == 60);
	assert(int_tbl_get(table, "f") == 20);

	// assering values of array
	assert(int_tbl_get(table, "a") == 60);
	assert(int_tbl_get(table, "b") == 10);
	assert(int_tbl_get(table, "c") == 30);
	assert(int_tbl_get(table, "d") == 40);
	assert(int_tbl_get(table, "e") == 50);
	assert(int_tbl_get(table, "f") == 20);


	// shrinking
	assert(int_tbl_shrink(table));

	// DESTRUCTION
	int_tbl_destroy(int_tbl_create());
	int_tbl_destroy(table);
	puts("All tests passed\n");
}

int main(void)
{
	test_list();
	test_table();
	return 0;
}
