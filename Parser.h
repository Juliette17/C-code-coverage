#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <memory>
#include "Scanner.h"
#include "Node.h"
#include "Program.h"
#include "Output_handler.h"
#include "Symbol.h"
#include "Expression.h"
#include "If_statement.h"

class Parser {

private:
	std::vector < std::shared_ptr<Symbol>> symbol_table;
	Scanner& scanner;
	std::shared_ptr<Node> tree_root;
	unsigned token_index;

public:
	Parser(Scanner& s) : scanner(s), tree_root(nullptr), token_index(0) {}

	void parse_program();
	std::vector < std::shared_ptr<Symbol>> get_symbol_table() { return symbol_table; }

private:
	Token go_to_next_token();
	Token go_to_previous_token();
	Token get_current_token();
	bool is_in_basic_operands(Token_type);
	bool is_in_arithmetic_operators(Token_type);
	bool is_rel_operator(Token_type);
	std::shared_ptr<Symbol> find_in_symbol_table(std::string);
	std::shared_ptr<Main_function> parse_main();
	std::shared_ptr<Define> parse_define();
	std::shared_ptr<Include> parse_include();
	std::shared_ptr<Var_declaration> parse_declaration(std::shared_ptr<Block>);
	std::shared_ptr<Assignement> parse_assignement(std::shared_ptr<Variable>, std::shared_ptr<Symbol>);
	std::shared_ptr<Expression> parse_expression();
	std::shared_ptr<Expression> parse_simple_expression();
	std::shared_ptr<Expression> parse_term();
	std::shared_ptr<Expression> parse_factor();
	std::shared_ptr<If_statement> parse_if();
	std::shared_ptr<While_statement> parse_while();
	std::shared_ptr<Instruction> parse_instruction(std::shared_ptr<Block>);
	std::shared_ptr<Condition_complex> parse_condition();
	std::shared_ptr<Scanf> parse_scanf();
	std::shared_ptr<Comment> parse_comment();
	
};



#endif //PARSER_H