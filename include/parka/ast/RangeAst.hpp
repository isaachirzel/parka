#ifndef PARKA_AST_RANGE_HPP
#define PARKA_AST_RANGE_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class RangeAst
	{
		Snippet _snippet;
		ExpressionAst* _bottom;
		ExpressionAst& _top;

	public:

		RangeAst(ExpressionAst& bottom, ExpressionAst& top):
			_snippet(bottom.snippet() + top.snippet()),
			_bottom(&bottom),
			_top(top)
		{}
		RangeAst(ExpressionAst& top):
			_snippet(top.snippet()),
			_bottom(nullptr),
			_top(top)
		{}
		RangeAst(RangeAst&&) = default;
		RangeAst(const RangeAst&) = delete;

		const auto& snippet() const { return _snippet; }
		bool hasBottom() const { return !!_bottom; }
		const auto& bottom() const { assert(_bottom); return *_bottom; }
		const auto& top() const { return _top; }
	};
}

#endif
