#ifndef PARKA_IR_TYPE_IR_HPP
#define PARKA_IR_TYPE_IR_HPP

namespace parka::ir
{
	struct TypeIr
	{
		virtual~TypeIr() {}

		virtual std::ostream& printType(std::ostream&) const = 0;

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type)
		{
			return type.printType(out);
		}
	};
}

#endif
