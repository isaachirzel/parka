#ifndef PARKA_AST_IDENTIFIER_AST_HPP
#define PARKA_AST_IDENTIFIER_AST_HPP

#include "parka/fs/FileSnippet.hpp"
#include <ostream>

namespace parka::ast
{
	class IdentifierAst
	{
		fs::FileSnippet _snippet;
		String _text;

	public:

		IdentifierAst(const fs::FileSnippet& snippet):
			_snippet(snippet),
			_text(snippet.ptr(), snippet.length())
		{}
		IdentifierAst(IdentifierAst&&) = default;
		IdentifierAst(const IdentifierAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& text() const { return _text; }

		operator const fs::FileSnippet&() const { return _snippet; }
		bool operator==(const IdentifierAst& other) const;
		friend std::ostream& operator<<(std::ostream& out, const IdentifierAst& identifier);
	};
}

#endif
