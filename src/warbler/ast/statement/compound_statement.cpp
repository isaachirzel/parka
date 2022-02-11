#include <warbler/ast/statement/compound_statement.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	CompoundStatement::CompoundStatement(Array<Ptr<Statement>>&& statements) :
	_statements(std::move(statements))
	{}

	Result<CompoundStatement> CompoundStatement::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LBRACE)
		{
			parse_error(iter, "compound statement starting with '{'");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		Array<Ptr<Statement>> statements;

		while (iter->type() != TOKEN_RBRACE)
		{
			auto res = Statement::parse(iter);

			if (!res)
				return res.error();

			statements.emplace_back(res.unwrap());
		}

		iter += 1;

		return CompoundStatement { std::move(statements) };
	}

	bool CompoundStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		for (auto& statement : _statements)
		{
			if (!statement->validate(mod_ctx, func_ctx))
				return false;
		}

		return true;
	}

	void CompoundStatement::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << "{\n";
		for (const auto& statement : _statements)
		{
			statement->print_tree(depth + 1);
		}
		std::cout << tree_branch(depth) << "}\n";
	}
}
