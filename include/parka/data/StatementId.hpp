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

	class StatementId
	{
		usize _index;
		StatementType _type;

	public:
		
		StatementId(StatementType type, usize index) :
		_index(index),
		_type(type)
		{}
		StatementId(StatementId&&) = default;
		StatementId(const StatementId&) = default;
		~StatementId() = default;
		StatementId& operator=(StatementId&&) = default;
		StatementId& operator=(const StatementId&) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
	};
}

#endif
