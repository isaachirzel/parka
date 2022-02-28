#include <warbler/syntax/statement/block_statement.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BlockStatement::BlockStatement(Array<Ptr<Statement>>&& statements) :
	_statements(std::move(statements))
	{}

	Result<BlockStatement> BlockStatement::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TokenType::LeftBrace)
		{
			print_parse_error(iter, "compound statement starting with '{'");
			return {};
		}

		iter += 1;

		Array<Ptr<Statement>> statements;

		while (iter->type() != lexicon::TokenType::RightBrace)
		{
			auto res = Statement::parse(iter);

			if (!res)
				return {};

			statements.emplace_back(res.unwrap());
		}

		iter += 1;

		return BlockStatement { std::move(statements) };
	}

	// bool BlockStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	func_ctx.blocks.push_back(&_context);

	// 	for (auto& statement : _statements)
	// 	{
	// 		if (!statement->validate(mod_ctx, func_ctx))
	// 			return false;
	// 	}

	// 	func_ctx.blocks.pop_back();

	// 	return true;
	// }

	void BlockStatement::print_tree(u32 depth) const
	{
		print_branch(depth, "{");
		
		for (const auto& statement : _statements)
		{
			statement->print_tree(depth + 1);
		}
		
		print_branch(depth, "}");
	}
}
