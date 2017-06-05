#ifndef RETURN_STATEMENT
#define RETURN_STATEMENT

#include "Libraries.h"

class Return_statement : public Node {
	Token token;
public:
	Node_type get_type() {
		return Node_type::RETURN;
	}
	Return_statement(Token token) { this->token = token; }
};

#endif
