#ifndef PARKA_AST_RANGE_HPP
#define PARKA_AST_RANGE_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class RangeAst
	{
		Snippet _snippet;
		ExpressionAst& _start;
		ExpressionAst* _end;

	public:

		RangeAst(ExpressionAst& start, ExpressionAst& end):
			_snippet(end.snippet() + start.snippet()),
			_start(start),
			_end(&end)
		{}
		RangeAst(ExpressionAst& start):
			_snippet(start.snippet()),
			_start(start),
			_end(nullptr)
		{}
		RangeAst(RangeAst&&) = default;
		RangeAst(const RangeAst&) = delete;

		const auto& snippet() const { return _snippet; }
		const auto& start() const { return _start; }
		bool hasEnd() const { return !!_end; }
		const auto& end() const { assert(_end); return *_end; }
	};
}

#endif
