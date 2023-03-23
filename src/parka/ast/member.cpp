#include "parka/ast/member.hpp"

#include "parka/util/print.hpp"

bool parseMember(Member *out, Token& token)
{
	if (token.type() == TokenType::KeywordPublic)
	{
		out->isPublic = true;
		token.increment();
	}
	else if (token.type() == TokenType::KeywordPrivate)
	{
		token.increment();
	}

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "member name", NULL);
		printNote("Trailing commas are not allowed.");
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	token.increment();

	if (token.type() != TokenType::Colon)
	{
		printParseError(token, "':' after member name", NULL);
		return false;
	}
	
	token.increment();

	if (!parseTypeAnnotation(&out->annotation, token))
		return false;

	return true;
}

bool parseMemberList(MemberList *out, Token& token)
{
	if (token.type() != TokenType::LeftBrace)
	{
		printParseError(token, "'{' before member list", NULL);
		return false;
	}

	token.increment();

	if (token.type() != TokenType::RightBrace)
	{
		while (true)
		{
			usize index = out->count;

			resizeArray(out->data, ++out->count);

			out->data[index] = (Member) { 0 };

			if (!parseMember(&out->data[index], token))
				return false;

			if (token.type() != TokenType::Comma)
				break;

			token.increment();
		}

		if (token.type() != TokenType::RightBrace)
		{
			printParseError(token, "'}' after struct body", NULL);
			return false;
		}
	}

	token.increment();

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
