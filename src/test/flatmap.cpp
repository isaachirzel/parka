

#include "parka/util/FlatMap.hpp"
#include "parka/util/String.hpp"
#include <iostream>

using namespace parka;

int main()
{
	auto map = FlatMap<String, int>();

	auto a = map.insert("WOW", 3);

	std::cout << "item: " << *a << std::endl;
}
