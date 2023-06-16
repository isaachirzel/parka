#ifndef PARKA_SYNTAX_IDENTIFIER_SYNTAX_HPP
#define PARKA_SYNTAX_IDENTIFIER_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

#include <ostream>

namespace parka
{
	class Identifier
	{
		Snippet _snippet;
		String _text;

	public:

		Identifier(const Snippet& snippet) :
		_snippet(snippet),
		_text(snippet.text())
		{}
		Identifier(Identifier&&) = default;
		Identifier(const Identifier&) = delete;

		static Optional<Identifier> parse(Token& token);

		const Snippet& snippet() const { return _snippet; }
		const auto& text() const { return _text; }

		operator const Snippet&() const { return _snippet; }
		bool operator==(const Identifier& other) const;
		friend std::ostream& operator<<(std::ostream& out, const Identifier& identifier);
	};
}

#endif
