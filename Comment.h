#ifndef COMMENT_H
#define COMMENT_H

#include "Node.h"

class Comment : public Node {

private:
	Token token;

public:
	Node_type get_type() {
		return Node_type::COMMENT;
	}

	Token get_token() { return token; }
	void set_token(Token token) { this->token = token; }
};

#endif