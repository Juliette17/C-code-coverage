#ifndef OUTPUT_HANDLER_H_INCLUDED
#define OUTPUT_HANDLER_H_INCLUDED

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include "Symbol.h"

class Test_generator;

class Output_handler {

public:
	void static scanning_successful(bool success = true);
	void static is_file_open(bool);

	void static parsing(std::string, std::string);
	void static show_symbol_table(std::vector < std::shared_ptr<Symbol>>);
	//void static show_test_sets(std::vector<std::vector<std::shared_ptr<Scanf>>>, std::vector < std::vector<std::shared_ptr<Executing_block>>>, std::string);
};


#endif // OUTPUT_HANDLER_H_INCLUDED