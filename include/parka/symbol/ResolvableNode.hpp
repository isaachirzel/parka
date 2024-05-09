#ifndef PARKA_SYMBOL_RESOLVABLE_NODE_HPP
#define PARKA_SYMBOL_RESOLVABLE_NODE_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/MemberAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/ast/VariableAst.hpp"

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
