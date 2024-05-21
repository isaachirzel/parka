#ifndef PARKA_AST_IDENTIFIER_AST_HPP
#define PARKA_AST_IDENTIFIER_AST_HPP

#include "parka/file/Snippet.hpp"
#include <ostream>

namespace parka::ast
{
	class IdentifierAst
	{
		Snippet _snippet;
		String _text;

	public:

		IdentifierAst(const Snippet& snippet):
			_snippet(snippet),
			_text(snippet.text())
		{}
		IdentifierAst(IdentifierAst&&) = default;
		IdentifierAst(const IdentifierAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& text() const { return _text; }

		operator const Snippet&() const { return _snippet; }
		bool operator==(const IdentifierAst& other) const;
		friend std::ostream& operator<<(std::ostream& out, const IdentifierAst& identifier);
	};
}

#endif
