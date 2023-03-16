#include "parka/ast/function.h"
#include "parka/ast/expression/literal.h"
#include "parka/ast/member.h"
#include "parka/ast/package.h"
#include "parka/ast/statement/statement.h"
#include "parka/ast/struct.h"
#include "parka/scope.h"
#include "parka/symbol_table.h"
#include "parka/util/array.h"
#include "parka/util/memory.h"
#include "parka/util/primitives.h"
#include "parka/util/print.h"
#include "parka/validator.h"

#include <string.h>

static const MemberList *getGlobalMembers(SymbolType type, usize index)
{
	switch (type)
	{
		case SYMBOL_STRUCT:
		{
			const Struct *node = symbolTableGetStruct(index);

			return &node->members;
		}

		default:
			break;
	}

	return NULL;
}

static const Member *getRecursiveMember(const MemberList *members, const char *key)
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

static bool validateTypeRecursion(SymbolType type, usize index)
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

static bool validateStructRecursion(usize index)
{
	return validateTypeRecursion(SYMBOL_STRUCT, index);
}

bool validate(void)
{
	bool success = true;

	if (!symbolTableForEachEntity(SYMBOL_PACKAGE, declarePackage))
		success = false;

	if (!symbolTableForEachEntity(SYMBOL_PACKAGE, validatePackage))
		success = false;

	if (!symbolTableForEachEntity(SYMBOL_STRUCT, validateStructRecursion))
		success = false;

	return success;
}
