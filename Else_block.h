#ifndef ELSE_BLOCK_H
#define ELSE_BLOCK_H

#include "Node.h"
#include "Block.h"

class Else_block : public Block
{
public:
	Node_type get_type() {
		return Node_type::ELSE_BLOCK;
	}
};

#endif