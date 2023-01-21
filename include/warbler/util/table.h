#ifndef WARLER_UTIL_HASHTABLE_H
#define WARLER_UTIL_HASHTABLE_H

#include "warbler/util/arena.h"
#include "warbler/util/primitives.h"

typedef struct TableEntry
{
	char *key;
	usize value;
	bool isDeleted;
} TableEntry;

typedef struct Table
{
	TableEntry *entries;
	usize primeNumberIndex;
	usize count;
} Table;

Table tableCreate(usize capacity);
void tableDestroy(Table *table);
void tableSet(Table *table, const char *key, usize value);

/**
 * @returns value associated with key or NOT_FOUND
 */
usize tableFind(Table *table, const char *key);
/**
 * @returns id of entry associated with key or first empty space
 */
TableEntry *tableGetEntry(Table *table, const char *key);

/**
 * @returns value associated with entry or NOT_FOUND
 */
usize tableEntryGetValue(TableEntry *entry);
void tableEntryInit(TableEntry *entry, const char *key, usize value);

#endif
