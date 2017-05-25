#ifndef SCANF_H
#define SCANF_H

#include "Node.h"

class Scanf_parameter : public Node {

private:
	Token token;

public:
	Token get_param() { return token; }
	Scanf_parameter(Token t) : token(t) {}

	Node_type get_type() {
		return Node_type::SCANF_PARAMETER;
	}
};

class Scanf : public Node {

private:
	std::vector < std::shared_ptr < Scanf_parameter >> parameters;

public:
	void add_to_parameters(std::shared_ptr < Scanf_parameter > p) { parameters.push_back(p); }
	std::vector<std::shared_ptr < Scanf_parameter >> get_parameters() { return parameters; }
	Node_type get_type() {
		return Node_type::SCANF;
	}
};




#endif