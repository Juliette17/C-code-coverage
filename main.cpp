#include <iostream>
#include <string>

#include "Scanner.h"
#include "Parser.h"
#include "Output_handler.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "No file specified" << std::endl;
	}
	else
	{
		std::string file = argv[1];
		//std::string file = "D:/Studia/TKOM/tkom_ok/testParser.c";
		Scanner scanner(file);
		Parser parser(scanner);
		parser.parse_program();
		Output_handler::show_symbol_table(parser.get_symbol_table());
	}
}