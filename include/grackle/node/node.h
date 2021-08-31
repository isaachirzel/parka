#ifndef NODE_H
#define NODE_H

// local includes
#include <grackle/data/token.h>
#include <vector>

class Node
{
public:
	virtual ~Node() = 0;
	virtual void verify() const = 0;
	virtual void print_tree() const = 0;
	virtual std::string to_c() const = 0;
};

#endif
