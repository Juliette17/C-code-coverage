#ifndef VARIABLE_H
#define VARIABLE_H

#include "Assigned.h"
#include "Token.h"
#include "Token_type.h"
#include "Symbol.h"
#include "Block.h"

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
	Variable(Token tok, std::shared_ptr<Block> scope) : token(tok) { 
		this->has_value = false; 
		this->name = token.get_value(); 
		std::shared_ptr<Symbol> found_symbol = scope->find_in_symbol_table(name);
		//std::sahred_ptr<Integer_symbol> int_sym = (Integer_symbol)found_symbol;
		if (found_symbol != nullptr && found_symbol->has_valuee())
		{
			this->has_value = true;
			double x = 1.0; //unnecessary random number
			value = found_symbol->get_value(x);
		}
		else
			this->has_value = false;

	}
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