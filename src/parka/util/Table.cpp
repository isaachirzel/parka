
#include "parka/log/Log.hpp"
#include "parka/util/Table.hpp"

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

		log::fatal("Unable to create table with capacity $. The maximum capacity is $.", minimumCapacity, maxCapacity);
	}
}
