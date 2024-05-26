

#include "parka/ir/TypeIr.hpp"
#include "parka/util/Set.hpp"
#include <iostream>

using namespace parka;
using namespace parka::ir;

int main()
{
	auto set = Set<TypeIr>(1024, 1'000'000);

	set.insert(TypeIr(TypeIr::boolType));
	set.insert(TypeIr(TypeIr::boolType));
	auto& a = set.insert(TypeIr(TypeIr::boolType));
	set.insert(TypeIr(TypeIr::charType));
	auto& b = set.insert(TypeIr(TypeIr::charType));

	std::cout << set.count() << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
}
