#include <iostream>
#include <string>
#include <sstream>

#include "Scanner.h"
#include "Parser.h"
#include "Output_handler.h"
#include "Test_generator.h"

int main(int argc, char* argv[])
{
	/*if (argc < 2)
	{
		std::cerr << "No file specified" << std::endl;
	}
	else
	{*/
		//std::string file = argv[1];

		std::string file = "testParser.c";
		Scanner scanner(file);
		/*std::ifstream t(file);
		std::stringstream buffer;
		buffer << t.rdbuf();
		std::cout << buffer.str() << std::endl;*/

		Parser parser(scanner);
		parser.parse_program();
		/*if (parser.get_tree_root() != nullptr)
			std::cout << "tree root" << std::endl;*/
		
		Output_handler::show_symbol_table(parser.get_symbol_table());
		std::shared_ptr<Block> block = parser.get_tree_root()->get_main();
		Test_generator test_generator(parser, file);

		int a;
		int b;
		/*while (block != nullptr)
		{
			Output_handler::show_symbol_table(block->get_symbol_table());
			 (int i = 0; i < block->get_blocks().size(); ++i)
			{
				Output_handler::show_symbol_table(block->get_blocks()[i]->get_symbol_table());
			}
			if (block->get_blocks().size() != 0)
				block = block->get_blocks()[0];
			else break;
		}*/
		/*Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_blocks()[0]->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_blocks()[1]->get_symbol_table());
		Output_handler::show_symbol_table(parser.get_tree_root()->get_main()->get_blocks()[0]->get_blocks()[2]->get_symbol_table());*/
		
		/*int number_of_vectors = test_generator.get_scopes().size();
		std::cout << "number of vectors " << number_of_vectors << std::endl;
		for (int i = 0; i < number_of_vectors; ++i)
		{
			std::shared_ptr<Block> scope = test_generator.get_scopes()[i][test_generator.get_scopes()[i].size() - 1];
			Output_handler::show_symbol_table(scope->get_symbol_table());
			std::cout << "scopes " << test_generator.get_scopes()[i].size() << std::endl;
			std::cout << "conditions " << test_generator.get_scopes()[i][test_generator.get_scopes()[i].size() - 1]->get_complex_conditions().size() << std::endl;
			//std::cout << "parents " << test_generator.get_scopes()[i][test_generator.get_scopes()[i].size() - 1]->get_parents().size() << std::endl;
			//std::cout << "condition values " << scope->get_condition_values().size() << std::endl;
		}

		std::vector<std::shared_ptr<Scanf>> scanfs = parser.get_all_scanfs_in_program();
		std::cout << "Generated scanf values " << std::endl << std::endl;
		for (int i = 0; i < parser.get_all_scanfs_in_program().size(); ++i)
		{
			std::shared_ptr<Scanf> scanf = scanfs[i];
			
			for (auto& param : scanf->get_parameters())
			{
				std::cout << param->get_param().get_value() << "\t"; //name 
				std::cout << param->get_value() << std::endl; //value
			}
		*/

		/*for (auto& a: test_generator.get_condition_values())
		{
			std::cout << a << std::endl;
		}*/
		

	//}
}