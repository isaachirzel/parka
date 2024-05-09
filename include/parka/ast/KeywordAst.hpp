#ifndef PARKA_AST_KEYWORD_HPP
#define PARKA_AST_KEYWORD_HPP

#include "parka/enum/KeywordType.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class KeywordAst
	{
		Snippet _snippet;
		KeywordType _type;

	public:

		KeywordAst(const Snippet& snippet, KeywordType type):
			_snippet(snippet),
			_type(type)
		{}
		KeywordAst(KeywordAst&&) = default;
		KeywordAst(const KeywordAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
	};
}

#endif
