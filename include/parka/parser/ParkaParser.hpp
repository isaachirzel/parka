#ifndef PARKA_PARSER_PARKA_PARSER_HPP
#define PARKA_PARSER_PARKA_PARSER_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/PrototypeAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ast/StatementAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/file/Directory.hpp"
#include "parka/parser/Parser.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Project.hpp"

namespace parka::parser
{
	class ParkaParser: public Parser
	{
		const Project& _project;

	public:
	
		ParkaParser(const Project& project):
		_project(project)
		{}
		ParkaParser(ParkaParser&&) = default;
		ParkaParser(const ParkaParser&) = delete;

		ast::Ast parse() const;
	};
}

#endif
