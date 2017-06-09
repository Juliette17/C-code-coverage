#ifndef SCANF_H
#define SCANF_H

#include "Node.h"
#include "Token.h"

class Scanf_parameter : public Node {

private:
	Token token;
	double value;

public:
	Token get_param() { return token; }
	Scanf_parameter(Token t) : token(t) {}
	void set_value(double val) { value = val; }
	double get_value() { return value; }


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
	std::shared_ptr<Scanf_parameter> get_parameter(std::string name)
	{
		for (auto& s : parameters)
		{
			if (s->get_param().get_value() == name)
			{
				return s;
			}
			
		}
		return nullptr;

	}
	Node_type get_type() {
		return Node_type::SCANF;
	}
};




#endif