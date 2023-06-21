#include "parka/ast/Member.hpp"
#include "parka/ir/Member.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	bool MemberAst::declareSelf(SymbolTable& parent)
	{
		_parent = &parent;

		return parent.declare(*this);
	}

	String MemberAst::getSymbol() const
	{
		// TODO: Differentiate between static and regular

		return name();
	}
}
