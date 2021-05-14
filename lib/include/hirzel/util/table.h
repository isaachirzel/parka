
#define HIRZEL_UTIL_TABLE_T int
// Error if no type declared
#ifndef HIRZEL_UTIL_TABLE_T
#error An element type must be defined for container
#endif

// Util macros
#define CONCAT(a, b) a##b
#define LSTR(s) #s
#define STR(s) LSTR(s)

// Type agnostic macros
#define HXT_BASE_NAME(type) 	CONCAT(hxtbl_, type)
#define HXT_ITEM_NAME(base)		CONCAT(base, _item)
#define HXT_STRUCT_NAME(base)	struct base
#define HXT_TYPEDEF_NAME(base)	CONCAT(base, _t)

// Convenient macro aliases
#define HXT_TYPE				HIRZEL_UTIL_TABLE_T
#define HXT_BASE				HXT_BASE_NAME(HXT_TYPE)
#define HXT_SIZES				CONCAT(HXT_BASE, _sizes)
#define HXT_ITEM_BASE			HXT_ITEM_NAME(HXT_BASE)
#define HXT_STRUCT				HXT_STRUCT_NAME(HXT_BASE)
#define HXT_ITEM				HXT_STRUCT_NAME(HXT_ITEM_BASE)
#define HXT_TYPEDEF				HXT_TYPEDEF_NAME(HXT_BASE)
#define HXT_ITEM_TYPEDEF		HXT_TYPEDEF_NAME(HXT_ITEM_BASE)

#define HXT_FUNC_BASE(base, postfix) CONCAT(base, postfix)
#define HXT_FUNC(name) HXT_FUNC_BASE(HXT_BASE, _##name)

// Declarations
#ifndef HIRZEL_UTIL_TABLE_H
#define HIRZEL_UTIL_TABLE_H

#include <stddef.h>
#include <stdio.h>

#define HXT_HASH_P		(97)
#define HXT_HASH_M		(1000000009)
#define HXT_INIT_SIZE	(11)	// prime number
#define HXT_PRIME_SIZES {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853,\
 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489 }

typedef HXT_ITEM
{
	char *key;
	HXT_TYPE value;
} HXT_ITEM_TYPEDEF;

typedef HXT_STRUCT
{
	size_t size;	// size of data
	size_t count;	// amount of elements
	HXT_ITEM *data;
} HXT_TYPEDEF;

extern long long unsigned hxhash(const char *str);

extern HXT_STRUCT *HXT_FUNC(create)();
extern void HXT_FUNC(destroy)(HXT_STRUCT *table);
extern bool HXT_FUNC(set)(HXT_STRUCT *table, const char* key, HXT_TYPE value);
extern HXT_TYPE HXT_FUNC(get)(HXT_STRUCT *table, const char *key);
extern HXT_TYPE *HXT_FUNC(getr)(HXT_STRUCT *table, const char *key);
extern bool HXT_FUNC(contains)(HXT_STRUCT *table, const char *key);

#endif

#ifdef HIRZEL_UTIL_TABLE_I
#undef HIRZEL_UTIL_TABLE_I

static size_t HXT_SIZES[] = HXT_PRIME_SIZES;


static HXT_ITEM HXT_FUNC(item_create)(const char *key, HXT_TYPE *value)
{
	HXT_ITEM item = {0};

	size_t len = strlen(key);
	item.key = malloc(len + 1);

	if (key)
	{
		strcpy(item.key, key);
		item.value = *value;
	}

	return item;
}

static void HXT_FUNC(item_destroy)(HXT_ITEM *item)
{
	free(item->key);
}

// CREATE
HXT_STRUCT *HXT_FUNC(create)()
{
	HXT_STRUCT *table = malloc(sizeof(HXT_STRUCT));
	if (!table) return NULL;
	table->data = calloc(HXT_INIT_SIZE, sizeof(HXT_ITEM));
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
void HXT_FUNC(destroy)(HXT_STRUCT *table)
{
	for (size_t i = 0; i < table->size; ++i)
	{
		if (!table->data[i].key) continue;
		HXT_FUNC(item_destroy(table->data + i));
	}

	free(table->data);
	free(table);
}

// CURRENTLY USES LINEAR PROBING
static void HXT_FUNC(insert)(HXT_STRUCT *table, HXT_ITEM* item)
{
	// getting starting pos
	size_t pos = hxhash(item->key) % table->size;
	// while space is occupied, increment
	size_t offs = 0;
	size_t i = pos;

	while (table->data[i].key != NULL)
	{
		offs += 1;
		i = (pos + offs * offs) % table->size;
	}
	// copying in element
	table->data[i] = *item;
}

// SET
bool HXT_FUNC(set)(HXT_STRUCT *table, const char* key, HXT_TYPE value)
{
	HXT_ITEM item = HXT_FUNC(item_create)(key, &value);

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
		HXT_ITEM *tmp = table->data;
		// allocating new buffer
		table->data = (HXT_ITEM*)calloc(new_size, sizeof(HXT_ITEM));
		// if data failed to allocate
		if (!table->data)
		{
			// clean up and exit
			table->data = tmp;
			HXT_FUNC(item_destroy)(&item);
			return false;
		}

		size_t old_size = table->size;
		table->size = new_size;		

		// copying over old data
		for (size_t i = 0; i < old_size; ++i)
		{
			// skip to non-null items
			if (!tmp[i].key) continue;
			HXT_FUNC(insert)(table, tmp + i);
		}

		// freeing old data
		free(tmp);
	}

	HXT_FUNC(insert)(table, &item);
	table->count += 1;
	return true;
}

HXT_TYPE *HXT_FUNC(getr)(HXT_STRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXT_TYPE *t = NULL;

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
HXT_TYPE HXT_FUNC(get)(HXT_STRUCT *table, const char *key)
{
	// initialized to 0 in case key is never found
	HXT_TYPE t = {0};
	HXT_TYPE *ref = HXT_FUNC(getr)(table, key);
	return (ref) ? *ref : t;
}

bool HXT_FUNC(contains)(HXT_STRUCT *table, const char *key)
{
	return (HXT_FUNC(getr)(table, key)) ? true : false;
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
