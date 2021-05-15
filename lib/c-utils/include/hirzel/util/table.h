//#define HIRZEL_CONTAINER_ITEM int
//#define HIRZEL_CONTAINER_NAME int_tbl

// Error if no type declared
#ifndef HIRZEL_CONTAINER_ITEM
#error An element type must be defined for list
#endif

#ifndef HIRZEL_CONTAINER_NAME
#error A struct name must be defined for list
#endif

// Util macros
#define HXCONCAT(a, b) a##b
#define HXSTRUCT_NAME(base) struct base
#define HXTYPEDEF_NAME(base) HXCONCAT(base, _t)
#define HXNODE_NAME(base) struct HXCONCAT(base, _node)
#define HXSYM_NAME(base, postfix) HXCONCAT(base, postfix)

// Convenient macro aliases
#define HXSTRUCT 	HXSTRUCT_NAME(HIRZEL_CONTAINER_NAME)
#define HXTYPEDEF 	HXTYPEDEF_NAME(HIRZEL_CONTAINER_NAME)
#define HXNODE		HXNODE_NAME(HIRZEL_CONTAINER_NAME)
#define HXITEM		HIRZEL_CONTAINER_ITEM
#define HXSYM(name) HXSYM_NAME(HIRZEL_CONTAINER_NAME, _##name)


#include <stddef.h>
#include <stdio.h>

#define HXHASH_P		(97)
#define HXHASH_M		(1000000009)
#define HXTABLE_SIZES {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853,\
 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489 }
 
HXNODE
{
	char *key;
	HXITEM value;
};

typedef HXSTRUCT
{
	unsigned size_idx;	// size of data
	size_t count;	// amount of stored keys
	HXNODE *data;	// data buffer
} HXTYPEDEF;

extern const size_t HXSYM(sizes)[];

extern long long unsigned HXSYM(hash)(const char *str);
extern HXSTRUCT *HXSYM(create)();
extern void HXSYM(destroy)(HXSTRUCT *table);
extern bool HXSYM(set)(HXSTRUCT *table, const char* key, HXITEM value);
extern bool HXSYM(set_ref)(HXSTRUCT *table, const char* key, HXITEM *value);
extern HXITEM HXSYM(get)(HXSTRUCT *table, const char *key);
extern HXITEM *HXSYM(get_ref)(HXSTRUCT *table, const char *key);
extern HXNODE *HXSYM(get_node)(HXSTRUCT *table, const char *key);
extern bool HXSYM(contains)(HXSTRUCT *table, const char *key);
extern bool HXSYM(empty)(HXSTRUCT *table);
extern void HXSYM(clear)(HXSTRUCT *table);
extern bool HXSYM(erase)(HXSTRUCT *table, const char *key);
extern bool HXSYM(shrink)(HXSTRUCT *table);
extern bool HXSYM(swap)(HXSTRUCT *table, const char *a, const char *b);
extern size_t HXSYM(size)(HXSTRUCT *table);
extern bool HXSYM(resize)(HXSTRUCT *table, unsigned new_size_idx);

#ifdef HIRZEL_IMPLEMENT
#undef HIRZEL_IMPLEMENT

const size_t HXSYM(sizes)[] = HXTABLE_SIZES;

static HXNODE HXSYM(node_create)(const char *key, HXITEM *value)
{
	HXNODE node = {0};
	if (!key) return node;
	size_t len = strlen(key);
	node.key = malloc(len + 1);
	strcpy(node.key, key);
	node.value = *value;

	return node;
}

static void HXSYM(node_destroy)(HXNODE *node)
{
	free(node->key);
}

// CREATE
HXSTRUCT *HXSYM(create)()
{
	HXSTRUCT *table = malloc(sizeof(HXSTRUCT));
	if (!table) return NULL;
	table->data = calloc(HXSYM(sizes)[0], sizeof(HXNODE));

	if (!table->data)
	{
		free(table);
		return NULL;
	}
	table->size_idx = 0;
	table->count = 0;
	return table;
}

// DESTROY
void HXSYM(destroy)(HXSTRUCT *table)
{
	size_t size = HXSYM(sizes)[table->size_idx];
	for (size_t i = 0; i < size; ++i)
	{
		if (!table->data[i].key) continue;
		HXSYM(node_destroy(table->data + i));
	}

	free(table->data);
	free(table);
}

// INSERT
void HXSYM(set_node)(HXSTRUCT *table, HXNODE* node)
{
	size_t size = HXSYM(sizes)[table->size_idx];
	// getting starting pos
	size_t pos = HXSYM(hash)(node->key) % size;
	
	// while space is occupied, increment
	size_t offs = 0;
	size_t i = pos;

	while (table->data[i].key != NULL)
	{
		offs += 1;
		i = (pos + offs * offs) % size;
	}
	// copying in node
	table->data[i] = *node;
}

bool HXSYM(resize)(HXSTRUCT *table, unsigned new_size_idx)
{
	// do nothing if new size is same as old
	if (new_size_idx == table->size_idx) return true;
	// storing old data
	HXNODE *tmp = table->data;
	size_t tmpc = HXSYM(sizes)[table->size_idx];

	// pointing to new data
	table->data = calloc(HXSYM(sizes)[new_size_idx], sizeof(HXNODE));

	if (!table->data)
	{
		// clean up and exit
		table->data = tmp;
		return false;
	}

	table->size_idx = new_size_idx;

	// copying over old data
	for (size_t i = 0; i < tmpc; ++i)
	{
		if (tmp[i].key) HXSYM(set_node)(table, tmp + i);
	}

	free(tmp);
	return true;
}

bool HXSYM(set_ref)(HXSTRUCT *table, const char* key, HXITEM *value)
{
	if (!key) return false;
	HXNODE node = HXSYM(node_create)(key, value);
	size_t size = HXSYM(sizes)[table->size_idx];
	// resizing when table is about half way full
	if ((size / (table->count + 1)) <= 1)
	{
		// getting new size of hash table
		// this will never fail, but it will stop growing after the last item
		// is reached but this will likeyly never happen
		char new_idx = table->size_idx;
		// if there is room to grow
		if (new_idx < (sizeof(HXSYM(sizes)) / sizeof(size_t)) - 1)
		{
			new_idx += 1;
		}

		bool res = HXSYM(resize)(table, new_idx);
		if (!res) return false;
	}
	
	HXSYM(set_node)(table, &node);
	table->count += 1;
	return true;
}

// SET
bool HXSYM(set)(HXSTRUCT *table, const char* key, HXITEM value)
{
	return HXSYM(set_ref)(table, key, &value);
}

HXNODE *HXSYM(get_node)(HXSTRUCT *table, const char *key)
{
	HXNODE *node = NULL;
	size_t size = HXSYM(sizes)[table->size_idx];
	// starting position for search
	size_t pos = HXSYM(hash)(key) % size;
	
	size_t offs = 0;
	size_t i = pos;

	// break if we hit null key
	while (table->data[i].key)
	{
		// if key matches
		if (strcmp(key, table->data[i].key) == 0)
		{
			node = table->data + i;
			break;
		}

		// quadratic probing
		offs += 1;
		// getting next position
		i = (pos + offs * offs) % size;
	}

	return node;
}

HXITEM *HXSYM(get_ref)(HXSTRUCT *table, const char *key)
{
	HXNODE *node = HXSYM(get_node)(table, key);
	return (node) ? &node->value : NULL;
}

// GET
HXITEM HXSYM(get)(HXSTRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXITEM t = {0};
	HXNODE *node = HXSYM(get_node)(table, key);
	return (node) ? node->value : t;
}

bool HXSYM(contains)(HXSTRUCT *table, const char *key)
{
	return (HXSYM(get_node)(table, key)) ? true : false;
}

bool HXSYM(erase)(HXSTRUCT *table, const char *key)
{
	HXNODE *node = HXSYM(get_node)(table, key);
	if (!node) return false;
	node->key = NULL;
	table->count -= 1;
	return true;
}

// hashing function
long long unsigned HXSYM(hash)(const char *str)
{
	long long unsigned hash = 0;
	long long unsigned pop = 1;

	while (*str)
	{
		hash = (hash + (*str - 'a' + 1) * pop) % HXHASH_M;
		pop = (pop * HXHASH_P) % HXHASH_M;
		str += 1;
	}

	return hash;
}

bool HXSYM(empty)(HXSTRUCT *table)
{
	return table->count == 0;
}

void HXSYM(clear)(HXSTRUCT *table)
{

	size_t size = HXSYM(sizes)[table->size_idx];
	for (size_t i = 0; i < size; ++i)
	{
		table->data[i].key = NULL;
	}
	table->count = 0;
}

size_t HXSYM(size)(HXSTRUCT *table)
{
	return HXSYM(sizes)[table->size_idx];
}

bool HXSYM(shrink)(HXSTRUCT *table)
{
	unsigned new_idx = 0;
	// find minimum size for current count
	for (unsigned i = 0; i < table->size_idx; ++i)
	{
		// get size from array
		size_t size = HXSYM(sizes)[i];
		// check if size is double or more than the count
		if ((size / table->count) > 1)
		{
			new_idx = i;
			break;
		}
	}

	return HXSYM(resize)(table, new_idx);
}

bool HXSYM(swap)(HXSTRUCT *table, const char *a, const char *b)
{
	// getting references to elements
	HXITEM *aref = HXSYM(get_ref)(table, a);
	if (!aref) return false;
	HXITEM *bref = HXSYM(get_ref)(table, b);
	if (!bref) return false;

	// swapping elements
	HXITEM i = *aref;
	*aref = *bref;
	*bref = i;

	// success
	return true;
}

#endif

// Preprocessor cleanup
#undef HIRZEL_CONTAINER_ITEM
#undef HIRZEL_CONTAINER_NAME
#undef HXCONCAT
#undef HXSTRUCT_NAME
#undef HXTYPEDEF_NAME
#undef HXNODE_NAME
#undef HXSYM_NAME
#undef HXSTRUCT
#undef HXTYPEDEF
#undef HXNODE
#undef HXITEM
#undef HXSYM
#undef HXHASH_P
#undef HXHASH_M
#undef HXTABLE_SIZES
