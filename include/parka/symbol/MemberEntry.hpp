#ifndef PARKA_SYMBOL_MEMBER_ENTRY_HPP
#define PARKA_SYMBOL_MEMBER_ENTRY_HPP

#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class MemberEntry: public Resolvable
	{
		const ast::MemberAst& _ast;

	public:
	
		MemberEntry(const ast::MemberAst& ast):
		Resolvable(ResolvableType::Member),
		_ast(ast)
		{}
		MemberEntry(MemberEntry&&) = default;
		MemberEntry(const MemberEntry&) = delete;

		const auto& ast() const { return _ast; }
	};
}

#endif
