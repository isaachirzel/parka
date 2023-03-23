#include "parka/local_symbol_table.hpp"

Block *LocalEntityTable::getCurrentBlock(LocalEntityTable&  restrict localTable)
{
	if (localTable->blockCount == 0)
		return NULL;

	BlockInfo *info = &localTable->blocks[localTable->blockCount - 1];

	return info->node;
}

void localSymbolTablePushBlock(LocalEntityTable& localTable, Block *block)
{
	usize index = localTable->blockCount;

	incrementArray(localTable->blocks, &localTable->blockCount, &localTable->blockCapacity);

	localTable->blocks[index] = (BlockInfo)
	{
		.node = block,
		.offset = localTable->symbolCount
	};
}

void localSymbolTablePopBlock(LocalEntityTable& localTable)
{
	assert(localTable->blockCount > 0);
	
	BlockInfo *block = &localTable->blocks[localTable->blockCount - 1];

	for (usize i = block->offset; i < localTable->symbolCount; ++i)
		symbolDestroy(&localTable->symbols[i]);

	localTable->blockCount -= 1;
	localTable->symbolCount = block->offset;
}

void localSymbolTableClear(LocalEntityTable& localTable)
{
	for (usize i = 0; i < localTable->symbolCount; ++i)
		symbolDestroy(&localTable->symbols[i]);

	localTable->function = NULL;
	localTable->symbolCount = 0;
	localTable->blockCount = 0;
}

const EntityContext *symbolTableFind(LocalEntityTable& localTable, const char *key)
{
	// TODO: Optimize by checking if there are ':' in the name to see if it's a local or global symbol
	EntityContext *local = findLocalSymbol(localTable, key, 0);

	if (local)
		return local;

	EntityContext *global = findGlobalSymbol(key);

	return global;
}

EntityContext *findLocalSymbol(LocalEntityTable& localTable, const char *identifier, usize blockOffset)
{
	if (localTable->symbolCount == 0)
		return NULL;

	usize i = localTable->symbolCount;

	do
	{
		i -= 1;

		EntityContext *symbol = &localTable->symbols[i];

		if (!strcmp(identifier, symbol->key))
			return symbol;
	}
	while (i > 0);

	return NULL;
}

EntityContext *findBlockSymbol(LocalEntityTable& localTable, const char *identifier)
{
	usize blockOffset = localTable->blockCount > 0
		? localTable->blocks[localTable->blockCount - 1].offset
		: 0;
	EntityContext *symbol = findLocalSymbol(localTable, identifier, blockOffset);

	return symbol;
}

bool symbolTableDeclareLocal(LocalEntityTable& localTable, EntityType type, usize index)
{
	const char *key = symbolGetKey(type, index);

	switch (type)
	{
		case EntityType::Variable:
		case EntityType::Parameter:
			break;
		
		default:
			exitWithErrorFmt("Unable to declare Local with EntityType: %d", type);
	}

	EntityContext *previous = findBlockSymbol(localTable, key);

	if (previous)
	{
		const Token& name = symbolGetToken(type, index);
		const Token& previousName = symbolGetToken(previous->type, previous->index);

		printTokenError(name, "'%s' is already declared in this block.", key);
		printTokenNote(previousName, "Previous declaration here.");

		previous->status = Invalid;

		return false;
	}

	usize symbolIndex = localTable->symbolCount;

	incrementArray(localTable->symbols, &localTable->symbolCount, &localTable->symbolCapacity);

	localTable->symbols[symbolIndex] = (EntityContext)
	{
		.key = stringDuplicate(key),
		.index = index,
		.type = type,
		.status = Pending
	};

	return true;
}
