#ifndef WHILE_STATEMENT_H
#define WHILE_STATEMENT_H

#include "Libraries.h"

class While_statement : public Block {

public:
	Node_type get_type() {
		return Node_type::WHILE_STATEMENT;
	}

};

#endif
