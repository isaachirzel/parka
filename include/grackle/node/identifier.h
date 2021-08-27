#ifndef IDENTIFIER_H
#define IDENTIFIER_H

// local includes
#include <grackle/node/node.h>
#include <grackle/data/token.h>

class Identifier : public Node
{
private:

	std::string_view _value;

public:

	Identifier(const std::vector<Token>::iterator &iter);
	~Identifier() {}

	void verify();
	void print_tree();
	std::string to_c();
};

#endif
