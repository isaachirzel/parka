#ifndef PARKA_AST_QUALIFIED_IDENTIFIER_HPP
#define PARKA_AST_QUALIFIED_IDENTIFIER_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class QualifiedIdentifier
	{
		Snippet _snippet;
		Array<Identifier> _parts;
		bool _isAbsolute;

	public:

		QualifiedIdentifier(const Snippet& snippet, Array<Identifier>&& parts, bool isAbsolute) :
		_snippet(snippet),
		_parts(std::move(parts)),
		_isAbsolute(isAbsolute)
		{
			assert(_parts.length() > 0);
		}
		QualifiedIdentifier(QualifiedIdentifier&&) = default;
		QualifiedIdentifier(const QualifiedIdentifier&) = delete;

		const auto& snippet() const { return _snippet; }
		const auto *begin() const { return _parts.begin(); }
		const auto *end() const { return _parts.end(); }
		const auto& length() const { return _parts.length(); }
		const auto& isAbsolute() const { return _isAbsolute; }

		const auto& operator[](usize index) const { return _parts[index]; }
		friend std::ostream& operator<<(std::ostream& out, const QualifiedIdentifier& identifier);
	};
}

#endif