#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

#include <warbler/syntax.h>
#include <warbler/directory.h>

// Expression
bool parseAdditiveExpression(ExpressionSyntax *out, Token *token);
bool parseBitwiseAndExpression(ExpressionSyntax *out, Token *token);
bool parseBitwiseOrExpression(ExpressionSyntax *out, Token *token);
bool parseBitwiseXorExpression(ExpressionSyntax *out, Token *token);
bool parseBooleanAndExpression(ExpressionSyntax *out, Token *token);
bool parseBooleanOrExpression(ExpressionSyntax *out, Token *token);
bool parseConditionalExpression(ExpressionSyntax *out, Token *token);
bool parseEqualityExpression(ExpressionSyntax *out, Token *token);
bool parseMultiplicativeExpression(ExpressionSyntax *out, Token *token);
bool parsePostfixExpression(ExpressionSyntax *out, Token *token);
bool parsePrefixExpression(ExpressionSyntax *out, Token *token);
bool parsePrimaryExpression(ExpressionSyntax *out, Token *token);
bool parseRelationalExpression(ExpressionSyntax *out, Token *token);
bool parseBitShiftExpression(ExpressionSyntax *out, Token *token);
bool parseSymbol(ExpressionSyntax *out, Token *token);
bool parseConstant(ExpressionSyntax *out, Token *token);
bool parseAssignment(ExpressionSyntax *out, Token *token);
bool parseBlock(ExpressionSyntax *out, Token *token);
bool parseExpression(ExpressionSyntax *out, Token *token);

// Function
bool parseFunction(FunctionSyntax *out, Token *token);
bool parseArgumentList(ArgumentListSyntax* out, Token *token);
bool parseParameter(ParameterSyntax *out, Token *token);
bool parseParameterList(ParameterListSyntax *out, Token *token);

// Statement
bool parseDeclaration(DeclarationSyntax *out, Token *token);
bool parseIfStatement(IfStatementSyntax *out, Token *token);
bool parseStatement(StatementSyntax *out, Token *token);

// Type
bool parseMember(MemberSyntax *out, Token *token);
bool parseStruct(StructSyntax *out, Token *token);
bool parseType(TypeSyntax *out, Token *token);
bool parseVariable(VariableSyntax *out, Token *token);
bool parseModule(ModuleSyntax *out, Token *token);
bool parse(ProgramSyntax *out, const Directory *directories, usize directoryCount);

#endif
