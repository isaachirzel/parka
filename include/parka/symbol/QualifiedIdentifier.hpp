#ifndef PARKA_SYNTAX_QUALIFIED_IDENTIFIER_SYNTAX_HPP
#define PARKA_SYNTAX_QUALIFIED_IDENTIFIER_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class QualifiedIdentifier
	{
		Array<Identifier> _parts;
		bool _isAbsolute;

	public:

		QualifiedIdentifier(Array<Identifier>&& parts, bool isAbsolute);
		QualifiedIdentifier(QualifiedIdentifier&&) = default;
		QualifiedIdentifier(const QualifiedIdentifier&) = delete;

		static Optional<QualifiedIdentifier> parse(Token& token);

		const auto *begin() const { return _parts.begin(); }
		const auto *end() const { return _parts.end(); }
		const auto& length() const { return _parts.length(); }
		const auto& isAbsolute() const { return _isAbsolute; }

		const auto& operator[](usize index) const { return _parts[index]; }
		friend std::ostream& operator<<(std::ostream& out, const QualifiedIdentifier& identifier);
	};
}

#endif