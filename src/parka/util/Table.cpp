
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace parka::table
{
	const usize primeNumbers[] =
	{
		11,
		23,
		47,
		97,
		197,
		397,
		797,
		1'597,
		3'203,
		6'421,
		12'853,
		25'717,
		51'437,
		102'877,
		205'759,
		411'527,
		823'117,
		1'646'237,
		3'292'489,
		6'584'983,
		13'169'977,
		26'339'969,
		52'679'969,
		105'359'939,
		210'719'881,
		421'439'783,
		842'879'579,
		1'685'759'167,
		3'371'518'343,
		// 6'743'036'717 -- this would make it too big for u32
	};
	
	const usize primeNumberCount = sizeof(primeNumbers) / sizeof(*primeNumbers);

	usize getCapacity(usize minimumCapacity)
	{
		for (usize i = 1; i < primeNumberCount; ++i)
		{
			auto capacity = primeNumbers[i];

			if (capacity >= minimumCapacity)
				return capacity;
		}

		usize maxCapacity = primeNumbers[primeNumberCount - 1];

		exitWithError("Unable to create table with capacity $. The maximum capacity is $.", minimumCapacity, maxCapacity);
	}
}

// TableEntry *tableGetEntry(Table *table, const char *key)
// {
// 	assert(table != nullptr);
// 	assert(key != nullptr);

// 	TableEntry *entries = table->entries;
// 	usize length = primeNumbers[table->primeNumberIndex];
// 	usize hash = hashKey(key);
// 	usize index = hash $ length;
// 	usize step = 0;

// 	while (true)
// 	{
// 		TableEntry *entry = &entries[index];

// 		if (entry->key == nullptr && !entry->isDeleted)
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
// 	assert(table != nullptr);
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
// 	assert(table != nullptr);
// 	assert(key != nullptr);

// 	TableEntry *entry = tableGetEntry(table, key);

// 	if (entry->key == nullptr)
// 	{
// 		*entry = tableEntryCreate(key, value);
// 		return;
// 	}

// 	entry->value = value;
// }

// usize tableFind(Table *table, const char *key)
// {
// 	assert(table != nullptr);
// 	assert(key != nullptr);
	
// 	TableEntry *entry = tableGetEntry(table, key);

// 	if (entry->key == nullptr)
// 		return NOT_FOUND;

// 	return entry->value;
// }


// usize tableEntryGetValue(TableEntry *entry)
// {
// 	if (entry->key == nullptr)
// 		return NOT_FOUND;

// 	return entry->value;
// }

// void tableEntryInit(TableEntry *entry, const char *key, usize value)
// {
// 	assert(entry != nullptr);
// 	assert(entry->key == nullptr);

// 	*entry = (TableEntry)
// 	{
// 		.key = stringDuplicate(key),
// 		.value = value
// 	};
// }

