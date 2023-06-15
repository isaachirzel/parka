// #ifndef PARKA_ENTITY_STATEMENT_ID_HPP
// #define PARKA_ENTITY_STATEMENT_ID_HPP

// #include "parka/enum/StatementType.hpp"
// #include "parka/util/Common.hpp"

// namespace parka
// {
// 	class StatementSyntaxId
// 	{
// 		usize _index;
// 		StatementType _type;

// 	private:

// 		StatementSyntaxId(StatementType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public:
		
// 		StatementSyntaxId(StatementSyntaxId&&) = default;
// 		StatementSyntaxId(const StatementSyntaxId&) = default;

// 		StatementSyntaxId& operator=(StatementSyntaxId&&) = default;
// 		StatementSyntaxId& operator=(const StatementSyntaxId&) = default;
// 		friend std::ostream& operator<<(std::ostream& out, const StatementSyntaxId& id);
// 		bool operator==(const StatementSyntaxId& other) const;

// 		friend struct StatementSyntax;
// 	};
// }

// #endif
