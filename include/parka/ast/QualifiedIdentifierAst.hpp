#ifndef PARKA_AST_QUALIFIED_IDENTIFIER_AST_HPP
#define PARKA_AST_QUALIFIED_IDENTIFIER_AST_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/util/Array.hpp"

namespace parka::ast
{
	class QualifiedIdentifierAst
	{
		Snippet _snippet;
		Array<IdentifierAst> _parts;
		bool _isAbsolute;

	public:

		QualifiedIdentifierAst(const Snippet& snippet, Array<IdentifierAst>&& parts, bool isAbsolute):
			_snippet(snippet),
			_parts(std::move(parts)),
			_isAbsolute(isAbsolute)
		{
			assert(_parts.length() > 0);
		}
		QualifiedIdentifierAst(QualifiedIdentifierAst&&) = default;
		QualifiedIdentifierAst(const QualifiedIdentifierAst&) = delete;

		const auto& snippet() const { return _snippet; }
		const IdentifierAst *begin() const { return _parts.begin(); }
		const IdentifierAst *end() const { return _parts.end(); }
		const auto& length() const { return _parts.length(); }
		const auto& isAbsolute() const { return _isAbsolute; }

		const auto& operator[](usize index) const { return _parts[index]; }
		friend std::ostream& operator<<(std::ostream& out, const QualifiedIdentifierAst& identifier);
	};
}

#endif