#include <iostream>
#include <string>
#include <sstream>

#include "Scanner.h"
#include "Parser.h"
#include "Output_handler.h"
#include "Test_generator.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "No file specified" << std::endl;
	}
	else
	{
		std::string file = argv[1];

		//std::string file = "testParser — kopia (8).c";
		Scanner scanner(file);
		Parser parser(scanner);
		parser.parse_program();
		Test_generator test_generator(parser, file);

		int a;
		int b;
		
		

	}
}