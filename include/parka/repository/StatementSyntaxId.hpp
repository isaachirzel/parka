#ifndef PARKA_ENTITY_STATEMENT_ID_HPP
#define PARKA_ENTITY_STATEMENT_ID_HPP

#include "parka/util/Primitives.hpp"

namespace parka
{
	enum class StatementType
	{
		DeclarationStatementSyntax,
		ExpressionSyntax,
		Jump
	};

	class StatementSyntaxId
	{
		usize _index;
		StatementType _type;

	public:
		
		StatementSyntaxId(StatementType type, usize index) :
		_index(index),
		_type(type)
		{}
		StatementSyntaxId(StatementSyntaxId&&) = default;
		StatementSyntaxId(const StatementSyntaxId&) = default;
		~StatementSyntaxId() = default;
		StatementSyntaxId& operator=(StatementSyntaxId&&) = default;
		StatementSyntaxId& operator=(const StatementSyntaxId&) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
	};
}

#endif
