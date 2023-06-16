#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class ExpressionAstId
	{
		usize _index;
		ExpressionType _type;

	private:

		ExpressionAstId(ExpressionType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:
		
		ExpressionAstId(ExpressionAstId&&) = default;
		ExpressionAstId(const ExpressionAstId&) = default;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		ExpressionAstId& operator=(ExpressionAstId&&) = default;
		ExpressionAstId& operator=(const ExpressionAstId&) = default;
		friend std::ostream& operator<<(std::ostream& out, const ExpressionAstId& id);
		bool operator==(const ExpressionAstId& other) const;

		friend struct ExpressionAst;
	};
}

#endif
