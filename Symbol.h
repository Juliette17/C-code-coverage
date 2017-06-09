#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <memory>
#include "Token_type.h"
#include "Scanf.h"
class Block;

class Symbol {

protected:
	std::string name;
	Identifier_type type;
	bool immutable;
	bool has_value;
	std::vector < std::shared_ptr<Scanf>> scanfs;
	double value;

	//scope in which the symbol was declared (main, while, if)
	std::shared_ptr<Block> scope; // if nullptr, program

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
	std::vector<std::shared_ptr<Scanf>> get_scanfs() { return scanfs; }
	void add_scanf(std::shared_ptr<Scanf> scanf) { scanfs.push_back(scanf); has_value = false; }
	void set_scope(std::shared_ptr<Block> scope) { this->scope = scope; }
	std::shared_ptr<Block> get_scope() { return scope; }
	virtual void set_value(double value) = 0;

	virtual double get_value(double) = 0;


};

class Integer_symbol : public Symbol {

private:
	int casted_value;
public:
	Integer_symbol(std::string name, Identifier_type type = Identifier_type::INT_ID , int value = 0, int casted_value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
		this->casted_value = casted_value;
	}
	std::string get_value() {
		return std::to_string(value); }
	double get_value(double d) { return casted_value; }


	void set_value(double value)
	{
		int val = (int)value;
		set_value(val);
	}
	void set_value(int value)
	{
		has_value = true;
		this->casted_value = value;
	}

};
class Character_symbol : public Symbol {
private:
	char casted_value;

public:
	Character_symbol(std::string name, Identifier_type type = Identifier_type::CHAR_ID, double value = 0, char casted_value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
		this->casted_value = casted_value;
	}
	std::string get_value() { return std::string(1,value); }

	double get_value(double d) { return casted_value; }
	void set_value(double value)
	{
		char val = (char)value;
		set_value(val);
	}
	void set_value(char value)
	{
		has_value = true;
		this->casted_value = value;
	}
};
class Float_symbol : public Symbol {

private:
	float casted_value;

public:

	Float_symbol(std::string name, Identifier_type type = Identifier_type::FLOAT_ID, float casted_value = 0, double value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
		this->casted_value = casted_value;
	}
	std::string get_value() { return std::to_string(value); }

	double get_value(double d) { return value; }
	void set_value(double value)
	{
		float val = (float)value;
		set_value(val);
	}
	void set_value(float value)
	{
		has_value = true;
		this->casted_value = value;
	}
};
class Double_symbol : public Symbol {

private:
	double casted_value;

public:

	Double_symbol(std::string name, Identifier_type type = Identifier_type::DOUBLE_ID, double value = 0, double casted_value = 0, bool has_value = false, bool immutable = false)
	{
		this->immutable = immutable;
		this->type = type;
		this->name = name;
		this->has_value = has_value;
		this->value = value;
		this->casted_value = casted_value;
	}

	std::string get_value() { return std::to_string(value); }
	double get_value(double d) { return value; }
	void set_value(double value)
	{
		has_value = true;
		this->value = value;
		this->casted_value = value;
	}
};



#endif //SYMBOL_H