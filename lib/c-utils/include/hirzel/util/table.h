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
#define HXELEM_NAME(base) struct HXCONCAT(base, _element)
#define HXFUNC_NAME(base, postfix) HXCONCAT(base, postfix)

// Convenient macro aliases
#define HXSTRUCT 	HXSTRUCT_NAME(HIRZEL_CONTAINER_NAME)
#define HXTYPEDEF 	HXTYPEDEF_NAME(HIRZEL_CONTAINER_NAME)
#define HXELEM		HXELEM_NAME(HIRZEL_CONTAINER_NAME)
#define HXITEM		HIRZEL_CONTAINER_ITEM
#define HXFUNC(name) HXFUNC_NAME(HIRZEL_CONTAINER_NAME, _##name)


#include <stddef.h>
#include <stdio.h>

#define HXT_HASH_P		(97)
#define HXT_HASH_M		(1000000009)
#define HXT_INIT_SIZE	(11)	// prime number
#define HXT_PRIME_SIZES {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853,\
 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489 }
 
HXELEM
{
	char *key;
	HXITEM value;
};

typedef HXSTRUCT
{
	size_t size;	// size of data
	size_t count;	// amount of elements
	HXELEM *data;
} HXTYPEDEF;

extern long long unsigned hxhash(const char *str);

extern HXSTRUCT *HXFUNC(create)();
extern void HXFUNC(destroy)(HXSTRUCT *table);
extern bool HXFUNC(set)(HXSTRUCT *table, const char* key, HXITEM value);
extern HXITEM HXFUNC(get)(HXSTRUCT *table, const char *key);
extern HXITEM *HXFUNC(getr)(HXSTRUCT *table, const char *key);
extern bool HXFUNC(contains)(HXSTRUCT *table, const char *key);


#ifdef HIRZEL_IMPLEMENT
#undef HIRZEL_IMPLEMENT

static size_t HXT_SIZES[] = HXT_PRIME_SIZES;


static HXELEM HXFUNC(element_create)(const char *key, HXITEM *value)
{
	HXELEM elem = {0};

	size_t len = strlen(key);
	elem.key = malloc(len + 1);

	if (key)
	{
		strcpy(elem.key, key);
		elem.value = *value;
	}

	return elem;
}

static void HXFUNC(element_destroy)(HXELEM *elem)
{
	free(elem->key);
}

// CREATE
HXSTRUCT *HXFUNC(create)()
{
	HXSTRUCT *table = malloc(sizeof(HXSTRUCT));
	if (!table) return NULL;
	table->data = calloc(HXT_INIT_SIZE, sizeof(HXITEM));
	if (!table->data)
	{
		free(table);
		return NULL;
	}
	table->size = HXT_SIZES[0];
	table->count = 0;
	return table;
}

// DESTROY
void HXFUNC(destroy)(HXSTRUCT *table)
{
	for (size_t i = 0; i < table->size; ++i)
	{
		if (!table->data[i].key) continue;
		HXFUNC(element_destroy(table->data + i));
	}

	free(table->data);
	free(table);
}

// CURRENTLY USES LINEAR PROBING
static void HXFUNC(insert)(HXSTRUCT *table, HXELEM* elem)
{
	// getting starting pos
	size_t pos = hxhash(elem->key) % table->size;
	// while space is occupied, increment
	size_t offs = 0;
	size_t i = pos;

	while (table->data[i].key != NULL)
	{
		offs += 1;
		i = (pos + offs * offs) % table->size;
	}
	// copying in element
	table->data[i] = *elem;
}

// SET
bool HXFUNC(set)(HXSTRUCT *table, const char* key, HXITEM value)
{
	HXELEM elem = HXFUNC(element_create)(key, &value);

	// resizing when table is about half way full
	if ((table->size / (table->count + 1)) <= 1)
	{
		// getting new size of hash table
		// this will never fail, but it will stop growing after the last item
		// is reached but this will likeyly never happen
		size_t new_size = table->size;
		for (int i = 1; i < sizeof(HXT_SIZES) / sizeof(size_t); ++i)
		{
			if (HXT_SIZES[i] > new_size)
			{
				new_size = HXT_SIZES[i];
				break;
			}
		}
	
		// temporary storage for old buffer
		HXELEM *tmp = table->data;
		// allocating new buffer
		table->data = (HXELEM*)calloc(new_size, sizeof(HXELEM));
		// if data failed to allocate
		if (!table->data)
		{
			// clean up and exit
			table->data = tmp;
			HXFUNC(element_destroy)(&elem);
			return false;
		}

		size_t old_size = table->size;
		table->size = new_size;		

		// copying over old data
		for (size_t i = 0; i < old_size; ++i)
		{
			// skip to non-null items
			if (!tmp[i].key) continue;
			HXFUNC(insert)(table, tmp + i);
		}

		// freeing old data
		free(tmp);
	}

	HXFUNC(insert)(table, &elem);
	table->count += 1;
	return true;
}

HXITEM *HXFUNC(getr)(HXSTRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXITEM *t = NULL;

	// starting position for search
	size_t pos = hxhash(key) % table->size;
	
	size_t offs = 0;
	size_t i = pos;

	while (table->data[i].key)
	{
		// if key matches
		if (strcmp(key, table->data[i].key) == 0)
		{
			t = &table->data[i].value;
			break;
		}

		// quadratic probing
		offs += 1;
		// getting next position
		i = (pos + offs * offs) % table->size;
	}

	return t;
}

// GET
HXITEM HXFUNC(get)(HXSTRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXITEM t = {0};
	HXITEM *ref = HXFUNC(getr)(table, key);
	return (ref) ? *ref : t;
}

bool HXFUNC(contains)(HXSTRUCT *table, const char *key)
{
	return (HXFUNC(getr)(table, key)) ? true : false;
}

// hashing function
long long unsigned hxhash(const char *str)
{
	long long unsigned hash = 0;
	long long unsigned pop = 1;

	while (*str)
	{
		hash = (hash + (*str - 'a' + 1) * pop) % HXT_HASH_M;
		pop = (pop * HXT_HASH_P) % HXT_HASH_M;
		str += 1;
	}

	return hash;
}

#endif

// Preprocessor cleanup
#undef HIRZEL_CONTAINER_ITEM
#undef HIRZEL_CONTAINER_NAME
#undef HXCONCAT
#undef HXSTRUCT_NAME
#undef HXTYPEDEF_NAME
#undef HXELEM_NAME
#undef HXFUNC_NAME
#undef HXSTRUCT
#undef HXTYPEDEF
#undef HXELEM
#undef HXITEM
#undef HXFUNC
