#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <memory>
#include "Defined_tokens.h"
#include "Token_type.h"

class Symbol {

protected:
	std::string name;
	Identifier_type type;
	bool immutable;
	bool has_value;

public:
	std::string get_name() { return name; }
	bool is_immutable() { return immutable; }
	void set_name(std::string name) { this->name = name; }
	Identifier_type get_type() { return type; }
	std::string get_identifier_type_name()
	{
		if (type == Identifier_type::INT_ID)
			return "int";
		if (type == Identifier_type::CHAR_ID)
			return "char";
		if (type == Identifier_type::FLOAT_ID)
			return "float";
		if (type == Identifier_type::DOUBLE_ID)
			return "double";
		if (type == Identifier_type::UNKNOWN)
			return "unknown";
	}
	bool has_valuee() { return has_value; }
	virtual std::string get_value() = 0;
	virtual void set_value(int v) { std::cout << "BASE" << std::endl; }
	virtual void set_value(char x) { std::cout << "BASE2" << std::endl; }

};

class Integer_symbol : public Symbol {

private:
	int value;
public:
	Integer_symbol(std::string name, Identifier_type type = Identifier_type::INT_ID , int value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
	}
	std::string get_value() {
		return std::to_string(value); }
	void set_value(int value)
	{
		has_value = true;
		this->value = value;
	}

};
class Character_symbol : public Symbol {
private:
	char value;

public:
	Character_symbol(std::string name, Identifier_type type = Identifier_type::INT_ID, char value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
	}
	std::string get_value() { return std::string(1,value); }
	void set_value(char value)
	{
		has_value = true;
		this->value = value;
	}
};
class Float_symbol : public Symbol {

private:
	float value;

public:

	Float_symbol(std::string name, Identifier_type type = Identifier_type::INT_ID, float value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
	}
	std::string get_value() { return std::to_string(value); }
	void set_value(float value)
	{
		has_value = true;
		this->value = value;
	}
};
class Double_symbol : public Symbol {

private:
	double value;

public:

	Double_symbol(std::string name, Identifier_type type = Identifier_type::INT_ID, double value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
	}

	std::string get_value() { return std::to_string(value); }
	void set_value(double value)
	{
		has_value = true;
		this->value = value;
	}
};



#endif //SYMBOL_H