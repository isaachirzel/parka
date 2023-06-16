// #ifndef PARKA_ENTITY_STATEMENT_ID_HPP
// #define PARKA_ENTITY_STATEMENT_ID_HPP

// #include "parka/enum/StatementType.hpp"
// #include "parka/util/Common.hpp"

// namespace parka
// {
// 	class StatementAstId
// 	{
// 		usize _index;
// 		StatementType _type;

// 	private:

// 		StatementAstId(StatementType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public:
		
// 		StatementAstId(StatementAstId&&) = default;
// 		StatementAstId(const StatementAstId&) = default;

// 		StatementAstId& operator=(StatementAstId&&) = default;
// 		StatementAstId& operator=(const StatementAstId&) = default;
// 		friend std::ostream& operator<<(std::ostream& out, const StatementAstId& id);
// 		bool operator==(const StatementAstId& other) const;

// 		friend struct StatementAst;
// 	};
// }

// #endif
