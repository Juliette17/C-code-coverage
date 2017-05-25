#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include "Token_type.h"
#include <string>
#include <fstream>

class Token {

private:
	int line_no;
	std::streampos token_pos;
	Token_type type;
	std::string value;

public:
	Token() : line_no(0), token_pos(0), type(Token_type::UNDEFINED), value("") {}
	Token(std::string t, int l_no, std::streampos c_pos, Token_type ty) : line_no(l_no), token_pos(c_pos), type(ty), value(t) {}
	
	//getters
	inline const int get_line_no() { return line_no; }
	inline const std::streampos get_token_pos() { return token_pos; }
	inline const Token_type get_type() { return type; }
	inline const std::string get_value() { return value; }
};


#endif // TOKEN_H_INCLUDED