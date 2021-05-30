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

extern long long unsigned HXSYM(hash)(const char *str, size_t len);
extern HXSTRUCT *HXSYM(create)();
extern void HXSYM(destroy)(HXSTRUCT *table);
// setters
extern bool HXSYM(set)(HXSTRUCT *table, const char* key, HXITEM value);
extern bool HXSYM(setn)(HXSTRUCT *table, const char* key, size_t len, HXITEM value);
extern bool HXSYM(setref)(HXSTRUCT *table, const char* key, HXITEM *value);
extern bool HXSYM(setnref)(HXSTRUCT *table, const char* key, size_t len, HXITEM *value);
extern void HXSYM(setnode)(HXSTRUCT *table, HXNODE* node);

extern HXITEM HXSYM(get)(HXSTRUCT *table, const char *key);
extern HXITEM HXSYM(getn)(HXSTRUCT *table, const char *key, size_t len);
extern HXITEM *HXSYM(getref)(HXSTRUCT *table, const char *key);
extern HXITEM *HXSYM(getnref)(HXSTRUCT *table, const char *key, size_t len);
extern HXNODE *HXSYM(getnode)(HXSTRUCT *table, const char *key, size_t len);

extern bool HXSYM(contains)(HXSTRUCT *table, const char *key);
extern bool HXSYM(containsn)(HXSTRUCT *table, const char *key, size_t len);
extern bool HXSYM(empty)(HXSTRUCT *table);
extern void HXSYM(clear)(HXSTRUCT *table);
extern bool HXSYM(erase)(HXSTRUCT *table, const char *key);
extern bool HXSYM(erasen)(HXSTRUCT *table, const char *key, size_t len);
extern bool HXSYM(shrink)(HXSTRUCT *table);
extern bool HXSYM(swap)(HXSTRUCT *table, const char *a, const char *b);
extern bool HXSYM(swapn)(HXSTRUCT *table, const char *a, size_t alen, const char *b, size_t blen);
extern size_t HXSYM(size)(HXSTRUCT *table);
extern bool HXSYM(resize)(HXSTRUCT *table, unsigned new_size_idx);

#ifdef HIRZEL_IMPLEMENT

const size_t HXSYM(sizes)[] = HXTABLE_SIZES;


static HXNODE HXSYM(node_create)(const char *key, size_t len, HXITEM *value)
{
	HXNODE node = {0};
	if (!key) return node;
	node.key = malloc(len + 1);
	strncpy(node.key, key, len);
	node.key[len] = 0;
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
	free(table);
}


// INSERT
void HXSYM(setnode)(HXSTRUCT *table, HXNODE* node)
{
	size_t size = HXSYM(sizes)[table->size_idx];
	// getting starting pos
	size_t pos = HXSYM(hash)(node->key, strlen(node->key)) % size;
	
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


// RESIZE
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
		if (tmp[i].key) HXSYM(setnode)(table, tmp + i);
	}

	free(tmp);
	return true;
}


// SETNREF
bool HXSYM(setnref)(HXSTRUCT *table, const char* key, size_t len, HXITEM *value)
{
	if (!key || !len) return false;
	HXNODE node = HXSYM(node_create)(key, len, value);
	size_t size = HXSYM(sizes)[table->size_idx];
	// resizing when table is about half way full
	if ((size / (table->count + 1)) <= 1)
	{
		// getting new size of hash table
		// this will never fail, but it will stop growing after the last item
		// is reached but this will likeyly never happen
		unsigned new_idx = table->size_idx;
		// if there is room to grow
		if (new_idx < (sizeof(HXSYM(sizes)) / sizeof(size_t)) - 1)
		{
			new_idx += 1;
		}

		bool res = HXSYM(resize)(table, new_idx);
		if (!res) return false;
	}
	
	HXSYM(setnode)(table, &node);
	table->count += 1;
	return true;
}


// SETREF
bool HXSYM(setref)(HXSTRUCT *table, const char* key, HXITEM *value)
{
	return HXSYM(setnref)(table, key, strlen(key), value);
}


// SETN
bool HXSYM(setn)(HXSTRUCT *table, const char *key, size_t len, HXITEM value)
{
	return HXSYM(setnref)(table, key, len, &value);
}


// SET
bool HXSYM(set)(HXSTRUCT *table, const char* key, HXITEM value)
{
	return HXSYM(setnref)(table, key, strlen(key), &value);
}


HXNODE *HXSYM(getnode)(HXSTRUCT *table, const char *key, size_t len)
{
	HXNODE *node = NULL;
	size_t size = HXSYM(sizes)[table->size_idx];
	// starting position for search
	size_t pos = HXSYM(hash)(key, len) % size;
	
	size_t offs = 0;
	size_t i = pos;

	// break if we hit null key
	while (table->data[i].key)
	{
		// if key matches
		if (strncmp(key, table->data[i].key, len) == 0)
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



// GET N REF
HXITEM *HXSYM(getnref)(HXSTRUCT *table, const char *key, size_t len)
{
	HXNODE *node = HXSYM(getnode)(table, key, len);
	return (node) ? &node->value : NULL;
}


// GET REF
HXITEM *HXSYM(getref)(HXSTRUCT *table, const char *key)
{
	HXNODE *node = HXSYM(getnode)(table, key, strlen(key));
	return (node) ? &node->value : NULL;
}


// GET N
HXITEM HXSYM(getn)(HXSTRUCT *table, const char *key, size_t len)
{
	HXITEM item = {0};
	HXNODE *node = HXSYM(getnode)(table, key, len);
	return (node) ? node->value : item;
}


// GET
HXITEM HXSYM(get)(HXSTRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXITEM t = {0};
	HXNODE *node = HXSYM(getnode)(table, key, strlen(key));
	return (node) ? node->value : t;
	
}



bool HXSYM(containsn)(HXSTRUCT *table, const char *key, size_t len)
{
	return (HXSYM(getnode)(table, key, len)) ? true : false;
}



// CONTAINS
bool HXSYM(contains)(HXSTRUCT *table, const char *key)
{
	return (HXSYM(getnode)(table, key, strlen(key))) ? true : false;
}


// ERASE N
bool HXSYM(erasen)(HXSTRUCT *table, const char *key, size_t len)
{
	HXNODE *node = HXSYM(getnode)(table, key, len);
	if (!node) return false;
	node->key = NULL;
	table->count -= 1;
	return true;
}


// ERASE
bool HXSYM(erase)(HXSTRUCT *table, const char *key)
{
	return HXSYM(erasen)(table, key, strlen(key));
}


// hashing function
long long unsigned HXSYM(hash)(const char *str, size_t len)
{
	long long unsigned hash = 0;
	long long unsigned pop = 1;

	for (size_t i = 0; i < len; ++i)
	{
		hash = (hash + (str[i] - 'a' + 1) * pop) % HXHASH_M;
		pop = (pop * HXHASH_P) % HXHASH_M;
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

bool HXSYM(swapn)(HXSTRUCT *table, const char *a, size_t alen, const char *b, size_t blen)
{
	// getting references to elements
	HXITEM *aref = HXSYM(getnref)(table, a, alen);
	if (!aref) return false;
	HXITEM *bref = HXSYM(getnref)(table, b, blen);
	if (!bref) return false;

	// swapping elements
	HXITEM i = *aref;
	*aref = *bref;
	*bref = i;

	// success
	return true;
}


bool HXSYM(swap)(HXSTRUCT *table, const char *a, const char *b)
{
	return HXSYM(swapn)(table, a, strlen(a), b, strlen(b));
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
