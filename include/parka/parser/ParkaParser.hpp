#ifndef PARKA_PARSER_PARKA_PARSER_HPP
#define PARKA_PARSER_PARKA_PARSER_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Operator.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Variable.hpp"
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
