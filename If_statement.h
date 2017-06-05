#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include "Block.h"
#include "Node.h"

class If_statement : public Block {

public:
	Node_type get_type() {
		return Node_type::IF_STATEMENT;
	}
};

#endif