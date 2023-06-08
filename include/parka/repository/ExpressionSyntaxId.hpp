#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class ExpressionSyntaxId
	{
		usize _index;
		ExpressionType _type;

	private:

		ExpressionSyntaxId(ExpressionType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:
		
		ExpressionSyntaxId(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId(const ExpressionSyntaxId&) = default;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		ExpressionSyntaxId& operator=(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId& operator=(const ExpressionSyntaxId&) = default;
		friend std::ostream& operator<<(std::ostream& out, const ExpressionSyntaxId& id);
		bool operator==(const ExpressionSyntaxId& other) const;

		friend struct ExpressionSyntax;
	};
}

#endif
