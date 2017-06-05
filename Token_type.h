#ifndef TOKEN_TYPE_H_INCLUDED
#define TOKEN_TYPE_H_INCLUDED


#include <vector>

enum Token_type : int {

	IDENTIFIER = 0, //NAME OF VARIABLE with _ inside
	TYPE_IDENTIFIER = 1, //int, char, float, double
	DEFINE = 2, // #define
	INCLUDE = 3, // #include <stdio.h>
	MAIN = 4, // main()	
	INTEGER_CONSTANT = 5, //PODZIELIÆ NA CA£KOWIT¥ I RZECZYWIST¥ ?
	REAL_CONSTANT = 6, // 1.57
	CHARACTER_CONSTANT = 7, // 'a'
	STRING = 8, // "some string"
	RETURN = 9,
	WHILE = 10,
	IF = 11,
	ELSE = 12,
	CONTINUE = 13,
	BREAK = 14,
	UNDEFINED = 15, // unknown
	COMMA = 16, // ,
	SEMICOLON = 17, // ;
	BRACE_OPEN = 18, // {
	BRACE_CLOSE = 19, // }
	PARENTHESE_OPEN = 20, // (
	PARENTHESE_CLOSE = 21, // )
	COMMENT = 22, // //
	PLUS = 23, // +
	MINUS = 24, // -
	MULTIPLY = 25, // *
	DIVIDE = 26, // /
	MODULO = 27, // %
	AND = 28, // &&
	OR = 29, // ||
	NEGATION = 30, // !
	EQUALITY = 31, // ==
	INEQUALITY = 32, // !=
	LESS = 33, // <
	GREATER = 34, // >
	LESS_OR_EQUAL = 35, // <=
	GREATER_OR_EQUAL = 36, // >=
	ASSIGNMENT = 37, // =
	SCANF = 38,  //"scanf"
	SCANF_ARGUMENT = 39, //&
	PRINTF = 40,
	EOFILE = 41

};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}


//names of token types
const std::vector<std::string> token_type_names = { "identifier", "type identifier", "directive #define", "directive #include <stdio.h>", "main()",
											  "integer constant", "real constant", "character_constant", "string", "return",
											  "while loop", "if statement", "else statement", "continue statement", "break statement", "undefined", "comma", "semicolon",
											  "brace open", "brace close", "parenthese open", "parenthese close", "comment",
											  "plus operator", "minus operator", "multiplication operator", "division operator", "modulo operator",
											  "and operator", "or operator", "negation operator", "equality operator", "inequality operator",
											  "less operator", "greater operator", "less-or-equal operator", "greater-or-equal operator",
											  "assignment operator", "scanf instruction", "ampersand - scanf operator", "printf instruction", "end of file" };
enum Identifier_type : int {
	UNKNOWN = 0, 
	CHAR_ID = 1,
	FLOAT_ID = 2,
	DOUBLE_ID = 3,
	INT_ID = 4
};

const std::vector<std::string> type_identifier_names = { "int", "char", "float", "double" };


#endif