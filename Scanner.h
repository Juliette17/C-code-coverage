#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
#include "Token.h"
#include "Output_handler.h"
#include "Error_handler.h"
#include "Token_type.h"
#include "Defined_tokens.h"

class Scanner {

private:
	std::ifstream input_stream;
	std::vector<Token> tokens;

public:
	Scanner(std::string file);
	std::vector<Token> get_tokens() { return tokens; }
	
	bool do_analysis();
	Token new_token(std::string, int, int, Token_type);

	bool is_in_basic_characters(char);
	bool is_end_of_token(char);
	bool is_in_keywords(std::string);


	/**************************************************
					Sign analysis
	**************************************************/
	void got_alpha(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_digit(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_sharp(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_comparison_sign(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_and_sign(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_or_sign(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_slash_sign(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_quotation_mark(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_double_quotation_mark(char &, char &, std::streampos &, int &, int &, std::string &);
	void got_basic_character(char &, char &, std::streampos &, int &, int &, std::string &);
};


#endif // SCANNER_H_INCLUDED