#ifndef TEST_GENERATOR
#define TEST_GENERATOR

#include "Parser.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits>

struct Executing_block {
	std::shared_ptr<Block> scope;
	bool executed;
	bool can_be_executed;
	int last_executed_instruction; //index in vector of scope->get_children()
	bool condition_value;
	std::vector<std::shared_ptr<Block>> parents;
	std::vector<std::shared_ptr<Symbol>> symbol_table;
	std::vector<std::shared_ptr<Scanf>> scanfs;
	Executing_block(std::shared_ptr<Block> scope,
		bool executed,
		int last_executed_instruction,
		std::vector<std::shared_ptr<Block>> parents,
		std::vector<std::shared_ptr<Symbol>> symbol_table,
		std::vector<std::shared_ptr<Scanf>> scanfs
		)
	{
		this->executed = executed;
		this->scope = scope;
		this->last_executed_instruction = last_executed_instruction;
		condition_value = false;
		this->parents = parents;
		this->symbol_table = symbol_table;
		this->scanfs = scanfs;
		this->can_be_executed = true;
	}
};

class Test_generator {

private:
	Parser& parser;
	std::string file_name;
	std::vector<std::vector<std::shared_ptr<Block>>> scopes;
	std::vector<bool> condition_values;
	std::vector<std::shared_ptr<Symbol>> symbol_table;
	std::vector<std::shared_ptr<Scanf>> scanfs;
	std::vector<std::shared_ptr<Executing_block>> executing_blocks;
	std::vector < std::vector<std::shared_ptr<Scanf>>> test_sets;
	std::vector<std::vector<std::shared_ptr<Executing_block>>> executed_in_test_sets;
	std::vector<std::shared_ptr<Executing_block>> executed_now;
	
	//int last_executed_instruction;

public:
	Test_generator(Parser& p, std::string f_name) : parser(p), file_name(f_name) {
		srand(time(NULL));
		init(); 
		run();
	}
	std::vector<std::shared_ptr<Symbol>> get_symbol_table() { return symbol_table; }
	std::vector<std::shared_ptr<Scanf>> get_scanfs() { return scanfs; }
	
	void add_to_symbol_table(std::shared_ptr<Symbol>);
	void add_to_scanfs(std::shared_ptr<Scanf>);
	void clear_symbol_tables();
	void clear_scanfs();
	void init_symbol_table_and_scanfs();
	void reset_all_scanfs();
	//int get_last_executed_instruction() { return last_executed_instruction; }
	//void set_last_executed_instruction(int a) { last_executed_instruction = a; }


	bool is_rel_operator(Token_type);
	bool is_conjunction_operator(Token_type);
	std::shared_ptr<Program> get_tree_root() { return parser.get_tree_root(); }
	//std::vector < std::shared_ptr<Symbol>> get_symbol_table() { return parser.get_symbol_table(); }

	void init();
	void run();
	void init_executing_blocks(std::shared_ptr<Executing_block>);

	//returns last executed instruction - typically Executing_block.scope->get_children().size()-1
	int execute_block_on_condition_true(std::shared_ptr<Executing_block>);
	char accept_instruction(std::shared_ptr<Instruction>, std::shared_ptr<Executing_block>);
	double calculate_expression(std::shared_ptr<Executing_block>, std::shared_ptr<Expression>, bool, bool, std::shared_ptr<Expression>);
	std::shared_ptr<Executing_block>find_executing_block(std::shared_ptr<Block>);
	std::shared_ptr<Scanf_parameter> in_scanfs(std::shared_ptr<Executing_block>, std::string);
	std::shared_ptr<Symbol> find_in_symbol_table(std::shared_ptr<Executing_block>, std::string);
	void change_symbol_in_table(std::shared_ptr<Symbol>, std::shared_ptr<Symbol>, std::shared_ptr<Executing_block>);
	void show_test_sets(std::vector<std::vector<std::shared_ptr<Scanf>>> , std::vector < std::vector<std::shared_ptr<Executing_block>>> ts, std::string );

	void add_to_scopes(std::vector<std::shared_ptr<Block>> scopes) { this->scopes.push_back(scopes); }
	void add_to_scopes(int index, std::shared_ptr<Block> scope) { scopes[index].push_back(scope); }
	std::vector<std::vector<std::shared_ptr<Block>>> get_scopes() {return scopes; }
	void Test_generator::analyze_scopes(std::vector<std::shared_ptr<Block>>);
	void Test_generator::analyze_conditions();
	void check_conditions();
	bool check_one_condition(std::shared_ptr<Block>);
	double portion_to_single_conditions(std::shared_ptr<Expression>, std::shared_ptr<Block>);
	void set_value_of_scanf_parameter(std::shared_ptr<Scanf>, std::string, double);
	void set_default_value_of_scanf_parameters();
	std::vector<bool> get_condition_values() { return condition_values; }
	

};


#endif test_generator