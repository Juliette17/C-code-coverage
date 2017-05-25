#ifndef COMMENT_H
#define COMMENT_H

#include "Node.h"

class Comment : public Node {

public:
	Node_type get_type() {
		return Node_type::COMMENT;
	}
};

#endif