#ifndef IDENTIFIER_H
#define IDENTIFIER_H

// local includes
#include <grackle/node/node.h>
#include <grackle/data/token.h>

namespace grackle
{
	class Identifier : public Node
	{
	private:

		std::string_view _value;

	public:

		Identifier(const TokenIter &iter);
		~Identifier() {}

		void verify() const override;
		void print_tree() const override;
		std::string to_c() const override;
	};
}

#endif
