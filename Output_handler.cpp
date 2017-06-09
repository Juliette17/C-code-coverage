#include "Output_handler.h"


void Output_handler::scanning_successful(bool success)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 5);
	success ? std::cout << "Scanning successfully completed." << std::endl
		: std::cout << "Scanning ended with fatal error." << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Output_handler::is_file_open(bool open)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 5);
	open ? std::cout << "File opened." << std::endl
		: std::cout << "Can't open file." << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Output_handler::parsing(std::string message, std::string token_value)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 5);
	std::cout << "Parsing ";
	std::cout << message << std::endl << token_value << std::endl;

	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Output_handler::show_symbol_table(std::vector < std::shared_ptr<Symbol>> st)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 3);
	std::cout << "\tSYMBOL TABLE " << std::endl << std::endl;
	std::cout << "type\tname\thas value\tscanfs" << std::endl << std::endl;
	if (st.size() == 0)
		std::cout << "No symbols in this scope" << std::endl;
	else
		for (auto& symbol : st)
		{	
			int scanfs_no = symbol->get_scanfs().size();
			double d = 1.0;
			std::cout << symbol->get_identifier_type_name() << "\t" << symbol->get_name() << "\t" << symbol->has_valuee() << "\t" << symbol->get_value(d) << "\t" << scanfs_no ;
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}