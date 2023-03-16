#include "parka/ast/member.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseMember(Member *out, Token *token)
{
	if (token->type == TOKEN_KEYWORD_PUBLIC)
	{
		out->isPublic = true;
		incrementToken(token);
	}
	else if (token->type == TOKEN_KEYWORD_PRIVATE)
	{
		incrementToken(token);
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "member name", NULL);
		printNote("Trailing commas are not allowed.");
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, "':' after member name", NULL);
		return false;
	}
	
	incrementToken(token);

	if (!parseTypeAnnotation(&out->annotation, token))
		return false;

	return true;
}

bool parseMemberList(MemberList *out, Token *token)
{
	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' before member list", NULL);
		return false;
	}

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_BRACE)
	{
		while (true)
		{
			usize index = out->count;

			resizeArray(out->data, ++out->count);

			out->data[index] = (Member) { 0 };

			if (!parseMember(&out->data[index], token))
				return false;

			if (token->type != TOKEN_COMMA)
				break;

			incrementToken(token);
		}

		if (token->type != TOKEN_RIGHT_BRACE)
		{
			printParseError(token, "'}' after struct body", NULL);
			return false;
		}
	}

	incrementToken(token);

	return true;
}

bool validateMemberList(MemberList *node, const Scope *packageScope)
{
	assert(node != NULL);
	assert(packageScope != NULL);

	bool success = true;

	for (usize i = 0; i < node->count; ++i)
	{
		Member *member = &node->data[i];

		for (usize j = 0; j < i; ++j)
		{
			const Member *previous = &node->data[j];

			if (tokenEquals(&member->name, &previous->name))
			{
				success = false;
				
				printTokenError(&member->name, "A member with same name is already declared in this struct.");
				printTokenNote(&previous->name, "Previous delcaration here.");

				break;
			}
		}

		if (!validateTypeAnnotation(&member->annotation, packageScope))
			success = false;
			// printTokenError(&member->name, "Declaration of member causes infinite recursion in struct '%s'.", node->symbol);
	}

	return success;
}

void memberFree(Member *node)
{
	typeAnnotationFree(&node->annotation);
}

void memberListFree(MemberList *node)
{
	for (usize i = 0; i < node->count; ++i)
		memberFree(&node->data[i]);

	deallocate(node->data);
}
