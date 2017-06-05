#ifndef OPERATOR_H
#define OPERATOR_H

#include "Libraries.h"

class Operator : public Node {
private:
	Token_type type; //+, -, etc

public:
	Operator(Token_type t) : type(t) {}
	Node_type get_type() {
		return Node_type::OPERATOR;
	}
	Token_type get_operator_type() { return type; }
};

#endif