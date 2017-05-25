#ifndef INCLUDE_H
#define INCLUDE_H

#include "Node.h"

class Include : public Node {
	Token token;
public:
	Node_type get_type() {
		return Node_type::INCLUDE;
	}
	Include(Token t) : token(t) {}
};

#endif