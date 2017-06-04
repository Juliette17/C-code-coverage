#include "Error_handler.h"

void Error_handler::invalid_character(char ch, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Unknown character: " << ch ;
	if (ch == '|')
		std::cerr << " Did you mean: || ? " << std::endl;
	else
		std::cerr << std::endl; 
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);		
}

void Error_handler::invalid_character_constant(std::string s, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Not proper number of characters in character constant: " << s;
	std::cerr << " Only 1 character between qingle quotation marks allowed.";
	std::cerr << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void Error_handler::quotation_not_closed(std::string s, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Quotation not closed: " << s ;
	std::cerr << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void Error_handler::invalid_character_in_number(std::string s, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Invalid characters in number: " << s;
	std::cerr << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void Error_handler::error_in_main(std::string s, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Missing parentheses: " << s;
	std::cerr << " Did you mean: main() ? " << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void Error_handler::invalid_directive(std::string s, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Invalid directive: " << s;
	std::cerr << " Did you mean: #include <stdio.h> or #define ? " << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Error_handler::unexpected_token(std::string wrong_token, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Unexpected token: " << wrong_token << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void Error_handler::expected_different_token(std::string wrong_token, int line_no, std::string expected_token)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Unexpected token: " << wrong_token;
	std::cerr << " Expected token: " << expected_token << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Error_handler::wrong_type(std::string wrong_type, int line_no, std::string expected_type)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Unexpected type of expression: " << wrong_type;
	std::cerr << " Expected type: " << expected_type << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Error_handler::undeclared_variable(std::string wrong_var, int line_no) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Variable undeclared: " << wrong_var << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Error_handler::variable_redefinition(std::string variable, int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Variable redefinition: " << variable << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void Error_handler::main_redefinition(int line_no)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cerr << "ERROR Line " << line_no << ": " << "Main already defined! " << std::endl;
	std::cerr << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}