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
		if (parser.get_tree_root() != nullptr)
			std::cout << "tree root" << std::endl;
		
		Output_handler::show_symbol_table(parser.get_symbol_table());
		std::shared_ptr<Block> block = parser.get_tree_root()->get_main();
		while (block != nullptr)
		{
			Output_handler::show_symbol_table(block->get_symbol_table());
			/* (int i = 0; i < block->get_blocks().size(); ++i)
			{
				Output_handler::show_symbol_table(block->get_blocks()[i]->get_symbol_table());
			}*/
			if (block->get_blocks().size() != 0)
				block = block->get_blocks()[0];
			else break;
		}
		/*Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_blocks()[0]->get_symbol_table());*/
	}
}