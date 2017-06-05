#ifndef VARIABLE_H
#define VARIABLE_H

#include "Assigned.h"
#include "Token.h"
#include "Token_type.h"

class Variable : public Assigned {

private:
	bool immutable;
	std::string name;
	double value;
	Token token;

public:
	Node_type get_type() {
		return Node_type::VARIABLE;
	}
	Variable(Token tok) : token(tok) {}
	Variable(std::string name, Identifier_type type = Identifier_type::INT_ID, double value = 0.0f, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->value = value;
		this->has_value = has_value;
	}

	//Identifier_type get_identifier_type() { return type; }
	std::string get_name() { return name; }
	double get_value() { return value; }

	bool is_immutable() { return immutable; }

	void set_value(int value)
	{
		has_value = true;
		this->value = value;
	}
	void set_value(float value)
	{
		has_value = true;
		this->value = value;
	}
	void set_value(double value)
	{
		has_value = true;
		this->value = value;
	}
	void set_value(char value)
	{
		has_value = true;
		this->value = value;
	}

};

#endif //variable_h