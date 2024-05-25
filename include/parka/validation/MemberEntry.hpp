#ifndef PARKA_VALIDATION_MEMBER_ENTRY_HPP
#define PARKA_VALIDATION_MEMBER_ENTRY_HPP

#include "parka/ast/MemberAst.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::validation
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

		Context* context() { return nullptr; }
		const auto& ast() const { return _ast; }
	};
}

#endif
