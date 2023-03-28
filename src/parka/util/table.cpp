
// #include "parka/util/print.hpp"
// #include "parka/util/string.hpp"
// #include "parka/util/table.hpp"

// #include <cassert>
// #include <cstdint>
// #include <cstdlib>
// #include <cstring>

// const usize primeNumbers[] =
// {
// 	11,
// 	23,
// 	47,
// 	97,
// 	197,
// 	397,
// 	797,
// 	1597,
// 	3203,
// 	6421,
// 	12853,
// 	25717,
// 	51437, 
// 	102877,
// 	205759,
// 	411527,
// 	823117,
// 	1646237,
// 	3292489,
// 	6584983,
// 	13169977,
// 	26339969,
// 	52679969,
// 	105359939,
// 	210719881,
// 	421439783,
// 	842879579,
// 	1685759167,
// 	3371518343,
// 	6743036717
// };
// const usize primeNumberCount = sizeof(primeNumbers) / sizeof(*primeNumbers);

// TableEntry tableEntryCreate(const char *key, usize valueIndex)
// {
// 	assert(key != NULL);

// 	TableEntry entry =
// 	{
// 		.key = stringDuplicate(key),
// 		.value = valueIndex
// 	};

// 	return entry;
// }

// void tableEntryDestroy(TableEntry *entry)
// {
// 	assert(entry != NULL);

// 	deallocate(entry->key);
// }

// void tableEntryDelete(TableEntry *entry)
// {
// 	assert(entry != NULL);
// 	deallocate(entry->key);

// 	entry->key = NULL;
// 	entry->value = 0;
// 	entry->isDeleted = true;
// }

// usize getPrimeNumberIndex(usize minCapacity)
// {
// 	for (usize i = 0; i < primeNumberCount; ++i)
// 	{
// 		if (primeNumbers[i] > minCapacity)
// 			return i;
// 	}

// 	usize maxCapacity = primeNumbers[primeNumberCount - 1];

// 	exitWithError("Unable to get Table size, requested capacity ($) is over maximum ($).", minCapacity, maxCapacity);
// }

// Table tableCreate(usize minCapacity)
// {
// 	const usize primeNumberIndex = getPrimeNumberIndex(minCapacity);
// 	const usize length = primeNumbers[primeNumberIndex];
// 	Table table =
// 	{
// 		.entries = allocateArray(sizeof(TableEntry), length),
// 		.primeNumberIndex = primeNumberIndex
// 	};

// 	return table;
// }

// void tableDestroy(Table *table)
// {
// 	assert(table != NULL);

// 	usize length = primeNumbers[table->primeNumberIndex];
// 	TableEntry *entries = table->entries;

// 	for (usize i = 0; i < length; ++i)
// 		tableEntryDestroy(&entries[i]);

// 	deallocate(table->entries);
// }

// usize hashKey(const char * key)
// {
// 	assert(key != NULL);

// 	const size_t p = 97;
// 	const size_t m = 1000000009;
// 	size_t hash = 0;
// 	size_t pop = 1;

// 	while (*key)
// 	{
// 		hash = (hash + (*key - 'a' + 1) * pop) $ m;
// 		pop = (pop * p) $ m;
// 		key += 1;
// 	}

// 	return hash;
// }

// TableEntry *tableGetEntry(Table *table, const char *key)
// {
// 	assert(table != NULL);
// 	assert(key != NULL);

// 	TableEntry *entries = table->entries;
// 	usize length = primeNumbers[table->primeNumberIndex];
// 	usize hash = hashKey(key);
// 	usize index = hash $ length;
// 	usize step = 0;

// 	while (true)
// 	{
// 		TableEntry *entry = &entries[index];

// 		if (entry->key == NULL && !entry->isDeleted)
// 			break;

// 		if (!strcmp(key, entry->key))
// 			break;

// 		step += 1;

// 		// TODO: Double check that this is correct
// 		index = (hash + step * step) $ length;
// 	}

// 	return &entries[index];
// }

// void tableResize(Table *table, usize newPrimeNumberIndex)
// {
// 	assert(table != NULL);
// 	assert(newPrimeNumberIndex < primeNumberCount);
// 	assert(primeNumbers[newPrimeNumberIndex] > table->count);

// 	if (newPrimeNumberIndex == table->primeNumberIndex)
// 		return;

// 	usize newLength = primeNumbers[newPrimeNumberIndex];
// 	TableEntry *newData = allocateArray(sizeof(TableEntry), newLength);

// 	usize oldLength = primeNumbers[table->primeNumberIndex];
// 	TableEntry *oldData = table->entries;

// 	table->entries = newData;
// 	table->primeNumberIndex = newPrimeNumberIndex;

// 	for (usize i = 0; i < oldLength; ++i)
// 	{
// 		const char *key = oldData[i].key;

// 		if (!key)
// 			continue;

// 		TableEntry *entry = tableGetEntry(table, key);

// 		*entry = oldData[i];
// 	}

// 	deallocate(oldData);
// }


// void tableSet(Table *table, const char *key, usize value)
// {
// 	assert(table != NULL);
// 	assert(key != NULL);

// 	TableEntry *entry = tableGetEntry(table, key);

// 	if (entry->key == NULL)
// 	{
// 		*entry = tableEntryCreate(key, value);
// 		return;
// 	}

// 	entry->value = value;
// }

// usize tableFind(Table *table, const char *key)
// {
// 	assert(table != NULL);
// 	assert(key != NULL);
	
// 	TableEntry *entry = tableGetEntry(table, key);

// 	if (entry->key == NULL)
// 		return NOT_FOUND;

// 	return entry->value;
// }


// usize tableEntryGetValue(TableEntry *entry)
// {
// 	if (entry->key == NULL)
// 		return NOT_FOUND;

// 	return entry->value;
// }

// void tableEntryInit(TableEntry *entry, const char *key, usize value)
// {
// 	assert(entry != NULL);
// 	assert(entry->key == NULL);

// 	*entry = (TableEntry)
// 	{
// 		.key = stringDuplicate(key),
// 		.value = value
// 	};
// }

