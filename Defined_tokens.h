#ifndef TKOM_MODULES_UTILS_KEYWORDS
#define TKOM_MODULES_UTILS_KEYWORDS

#include <unordered_map>
#include <vector>
#include <string>
#include <set>

//#include "Libraries.h"

const std::unordered_map<std::string, Token_type> keywords = {
	{ "#define", Token_type::DEFINE },
	{ "#include <stdio.h>", Token_type::INCLUDE },
	{ "int main()", Token_type::MAIN },
	{ "int", Token_type::TYPE_IDENTIFIER },
	{ "char", Token_type::TYPE_IDENTIFIER },
	{ "float", Token_type::TYPE_IDENTIFIER },
	{ "double", Token_type::TYPE_IDENTIFIER },
	{ "if", Token_type::IF },
	{ "while", Token_type::WHILE },
	{ "else", Token_type::ELSE },
	{ "return", Token_type::RETURN },
	{ "continue", Token_type::CONTINUE },
	{ "break", Token_type::BREAK },
	{ "scanf", Token_type::SCANF },
	{ "printf", Token_type::PRINTF }
};

const std::unordered_map<char, Token_type> basic_characters = {
	{ ',', Token_type::COMMA },
	{ ';', Token_type::SEMICOLON },
	{ '(', Token_type::PARENTHESE_OPEN },
	{ ')', Token_type::PARENTHESE_CLOSE },
	{ '{', Token_type::BRACE_OPEN },
	{ '}', Token_type::BRACE_CLOSE },
	{ '+', Token_type::PLUS },
	{ '-', Token_type::MINUS },
	{ '*', Token_type::MULTIPLY },
	{ '/', Token_type::DIVIDE },
	{ '%', Token_type::MODULO },
	{ '=', Token_type::ASSIGNMENT },
	{ '!', Token_type::NEGATION },
	{ '<', Token_type::LESS },
	{ '>', Token_type::GREATER }
};

const std::unordered_map<std::string, Token_type> double_operators = {
	{ "==", Token_type::EQUALITY },
	{ "!=", Token_type::INEQUALITY },
	{ "<=", Token_type::LESS_OR_EQUAL },
	{ ">=", Token_type::GREATER_OR_EQUAL },
	{ "&&", Token_type::AND },
	{ "||", Token_type::OR },
	{ "//", Token_type::COMMENT }

};

const std::vector<char> end_of_token = { '=', '!', '<', '>', '&', '|', ',', '\'', '\"', ';', '(', ')', '{', '}', 
										 '+', '-', '*', '/', '%' };

const std::set<Token_type> operand_literals = {Token_type::REAL_CONSTANT, Token_type::INTEGER_CONSTANT, Token_type::IDENTIFIER };
const std::set<Token_type> aritmetic_operators = {Token_type::PLUS, Token_type::MINUS, Token_type::MULTIPLY, Token_type::DIVIDE, Token_type::MODULO };
const std::set<Token_type> rel_operators = {Token_type::EQUALITY, Token_type::INEQUALITY, Token_type::LESS_OR_EQUAL, Token_type::LESS, Token_type::GREATER, Token_type::GREATER_OR_EQUAL};

#endif
