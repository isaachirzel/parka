#ifndef PARKA_PARSER_PARSER_HPP
#define PARKA_PARSER_PARSER_HPP

#include "parka/ast/Ast.hpp"
namespace parka::parser
{
	struct Parser
	{
		virtual ~Parser() {}

		virtual ast::Ast parse() = 0;
	};
}

#endif
