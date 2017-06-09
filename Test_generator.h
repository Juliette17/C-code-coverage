#ifndef TEST_GENERATOR
#define TEST_GENERATOR

#include "Parser.h"
#include <vector>

struct Executing_block {
	std::shared_ptr<Block> scope;
	bool executed;
	int last_executed_instruction;
	bool condition_value;
	std::vector<std::shared_ptr<Block>> parents;
	Executing_block(std::shared_ptr<Block> scope,
		bool executed,
		int last_executed_instruction,
		std::vector<std::shared_ptr<Block>> parents
		)
	{
		this->executed = executed;
		this->scope = scope;
		this->last_executed_instruction = last_executed_instruction;
		condition_value = false;
		parents = parents;
	}
};

class Test_generator {

private:
	Parser& parser;
	std::vector<std::vector<std::shared_ptr<Block>>> scopes;
	std::vector<bool> condition_values;
	std::vector<std::shared_ptr<Symbol>> symbol_table;
	std::vector<std::shared_ptr<Scanf>> scanfs;
	std::vector<Executing_block> executing_blocks;

	
	//int last_executed_instruction;

public:
	Test_generator(Parser& p) : parser(p) { init(); }
	std::vector<std::shared_ptr<Symbol>> get_symbol_table() { return symbol_table; }
	std::vector<std::shared_ptr<Scanf>> get_scanfs() { return scanfs; }
	
	void add_to_symbol_table(std::shared_ptr<Symbol>);
	void add_to_scanfs(std::shared_ptr<Scanf>);
	void clear_symbol_table();
	void clear_scanfs();
	void init_symbol_table_and_scanfs();
	//int get_last_executed_instruction() { return last_executed_instruction; }
	//void set_last_executed_instruction(int a) { last_executed_instruction = a; }


	bool is_rel_operator(Token_type);
	bool is_conjunction_operator(Token_type);
	std::shared_ptr<Program> get_tree_root() { return parser.get_tree_root(); }
	//std::vector < std::shared_ptr<Symbol>> get_symbol_table() { return parser.get_symbol_table(); }

	void init();
	void run();
	void init_executing_blocks(Executing_block);
	void execute_block_on_condition_true(std::shared_ptr<Block>);
	double calculate_condition(std::shared_ptr<Expression>);



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