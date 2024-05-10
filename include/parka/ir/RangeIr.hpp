#ifndef PARKA_IR_RANGE_IR_HPP
#define PARKA_IR_RANGE_IR_HPP

#include "parka/ir/ExpressionIr.hpp"
namespace parka::ir
{
	class RangeIr
	{
		ExpressionIr& _start;
		ExpressionIr* _end;

	public:

		RangeIr(ExpressionIr& start):
			_start(start),
			_end(nullptr)
		{}
		RangeIr(ExpressionIr& start, ExpressionIr& end):
			_start(start),
			_end(&end)
		{}
		RangeIr(RangeIr&&) = default;
		RangeIr(const RangeIr&) = delete;

		const auto& start() const { return _start; }
		bool hasEnd() const { return !!_end; }
		const auto& end() const { return *_end; }
	};
}

#endif
