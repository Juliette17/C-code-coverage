#ifndef ERROR_HANDLER_H_INCLUDED
#define ERROR_HANDLER_H_INCLUDED


#include <string>
#include <iostream>
#include <Windows.h>

class Error_handler {

public:
	/*****************************************
				Scanner errors
	*****************************************/
	void static invalid_character(char, int);
	void static invalid_character_constant(std::string, int);
	void static quotation_not_closed(std::string, int);
	void static invalid_character_in_number(std::string, int);
	void static error_in_main(std::string, int);
	void static invalid_directive(std::string, int);

	void static unexpected_token(std::string, int);
	void static expected_different_token(std::string, int, std::string);
	void static wrong_type(std::string, int, std::string);
	void static undeclared_variable(std::string, int);

};

#endif // ERROR_HANDLER_H_INCLUDED