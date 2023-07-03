#ifndef PARKA_SYMBOL_RESOLVABLE_NODE_HPP
#define PARKA_SYMBOL_RESOLVABLE_NODE_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Member.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/ast/Variable.hpp"

namespace parka
{
	template <typename AstType, typename IrType, ResolvableType resolvableType>
	class ResolvableNode: public Resolvable
	{
		const AstType& _ast;
		const IrType *_ir;

	public:

		ResolvableNode(const T& ast):
		Resolvable(resolvableType),
		_ast(ast),
		_ir(nullptr)
		{}
		ResolvableNode(ResolvableNode&&) = default;
		ResolvableNode(const ResolvableNode&) = default;

		const AstType& ast() const { return _ast; }
		const IrType *ir() const { return _ir; }
		const String& name() const { return _node.name(); }
	};

	using ResolvableVariable = ResolvableNode<ast::VariableAst, ir::VariableIr ResolvableType::Variable>;
	using ResolvableMember = ResolvableNode<ast::MemberAst, ir::MemberIr ResolvableType::Member>;
	using ResolvableParameter = ResolvableNode<ast::ParameterAst, ir::ParameterIr ResolvableType::Parameter>;
}

#endif
