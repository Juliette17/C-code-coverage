#ifndef SCANF_H
#define SCANF_H

#include "Node.h"
#include "Token.h"

class Scanf_parameter : public Node {

private:
	Token token;
	double value;
	double test_value;
	std::vector<double> prohibited;
	double min_value;
	double max_value;

public:
	bool has_min_value;
	bool has_max_value;
	bool has_value;
	Token get_param() { return token; }
	Scanf_parameter(Token t) : token(t) 
	{
		has_min_value = false;
		has_max_value = false;
		has_value = false;
		min_value = 0;
		max_value = 0;
			value = 0;
	}
	void set_min_value(double val) { has_min_value = true;  min_value = val; }
	void set_max_value(double val) { has_max_value = true;  max_value = val; }
	void set_value(double val) { has_value = true;  value = val; }
	double get_value() { return value; }
	double get_min_value() { return min_value; }
	double get_max_value() { return max_value; }
	void add_prohibited(double p) { prohibited.push_back(p); }
	std::vector<double> get_prohibited() { return prohibited; }
	void set_test_value(double val) { test_value = val; }
	double get_test_value() { return test_value; }



	Node_type get_type() {
		return Node_type::SCANF_PARAMETER;
	}
};

class Scanf : public Node {

private:
	std::vector < std::shared_ptr < Scanf_parameter >> parameters;
	int line_no;

public:
	Scanf(int l_no) : line_no(l_no) {}
	int get_line_no() { return line_no; }

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