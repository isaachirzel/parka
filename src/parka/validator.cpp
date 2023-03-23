#include "parka/ast/function.hpp"
#include "parka/ast/expression/literal.hpp"
#include "parka/ast/member.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/ast/struct.hpp"
#include "parka/scope.hpp"
#include "parka/global_symbol_table.hpp"
#include "parka/util/array.hpp"

#include "parka/util/primitives.hpp"
#include "parka/util/print.hpp"
#include "parka/validator.hpp"

#include <string.h>

const MemberList *getGlobalMembers(EntityType type, usize index)
{
	switch (type)
	{
		case EntityType::Struct:
		{
			const Struct *node = symbolTableGetStruct(index);

			return &node->members;
		}

		default:
			break;
	}

	return NULL;
}

const Member *getRecursiveMember(const MemberList *members, const char *key)
{
	for (usize i = 0; i < members->count; ++i)
	{
		const Member *member = &members->data[i];
		const Type *memberType = &member->annotation.type;
		const char *memberTypeKey = symbolGetKey(memberType->type, memberType->index);
		// TODO: Indirection check

		if (!strcmp(memberTypeKey, key))
			return member;

		const MemberList *memberTypeMembers = getGlobalMembers(memberType->type, memberType->index);

		if (!memberTypeMembers)
			continue;

		if (getRecursiveMember(memberTypeMembers, key))
			return member;
	}
	
	return NULL;
}

bool validateTypeRecursion(EntityType type, usize index)
{
	const MemberList *members = getGlobalMembers(type, index);

	if (!members)
		return true;

	const char *key = symbolGetKey(type, index);
	const Member *recursiveMember = getRecursiveMember(members, key);

	if (recursiveMember)
	{
		printTokenError(&recursiveMember->name, "Declaration of member creates recursive type");
		return false;
	}

	return true;
}

bool validateStructRecursion(usize index)
{
	return validateTypeRecursion(EntityType::Struct, index);
}

bool validate(void)
{
	bool success = true;

	if (!symbolTableForEachEntity(EntityType::Package, declarePackage))
		success = false;

	if (!symbolTableForEachEntity(EntityType::Package, validatePackage))
		success = false;

	if (!symbolTableForEachEntity(EntityType::Struct, validateStructRecursion))
		success = false;

	return success;
}
