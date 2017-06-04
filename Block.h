#ifndef BLOCK_H
#define BLOCK_H

#include "Node.h"
//#include "Instruction.h"
//#include "Loop_stop.h"
//#include "Comment.h"
//#include "Return_statement.h"
#include <vector>
//#include "Symbol.h"

class Block : public Node {

protected:
	std::vector<std::shared_ptr<Instruction>> instructions;
	std::vector<std::shared_ptr<Block>> blocks;
	std::vector<std::shared_ptr<Comment>> comments;
	std::vector<std::shared_ptr<Return_statement>> returns;
	std::vector<std::shared_ptr<Loop_stop>> loop_stops;
	std::shared_ptr<Condition> condition;
	std::vector<std::shared_ptr<Symbol>> symbol_table;


public:
	std::vector<std::shared_ptr<Instruction>> get_instructions() { return instructions; }
	std::vector<std::shared_ptr<Block>> get_blocks() { return blocks; }
	std::vector<std::shared_ptr<Comment>> get_comments() { return comments; }
	std::vector<std::shared_ptr<Return_statement>> get_returns() { return returns; }

	void add_to_instructions(std::shared_ptr<Instruction> instruction) { this->instructions.push_back(instruction); }
	void add_to_blocks(std::shared_ptr<Block> block) { this->blocks.push_back(block); }
	void add_to_comments(std::shared_ptr<Comment> comment) { this->comments.push_back(comment); }
	void add_to_returns(std::shared_ptr<Return_statement> ret) { this->returns.push_back(ret); }

	void add_comment(std::shared_ptr<Comment> com) { comments.push_back(com); }
	std::vector<std::shared_ptr<Loop_stop>> get_loop_stops() { return loop_stops; }
	void add_loop_stops(std::shared_ptr<Loop_stop> ls) { loop_stops.push_back(ls); }
	std::shared_ptr<Condition> get_condition() { return condition; }
	void set_condition(std::shared_ptr<Condition> cond) { this->condition = cond; }

	std::shared_ptr<Symbol> find_in_symbol_table(std::shared_ptr<Symbol> symbol)
	{
		for (auto& s : symbol_table)
		{
			if (s->get_name() == symbol->get_name())
			{
				return s;
			}
		}
		return nullptr;
	}

	void add_to_symbol_table(std::shared_ptr<Symbol> symbol)
	{	
		std::shared_ptr<Symbol> new_symbol = find_in_symbol_table(symbol);
		if (new_symbol != nullptr)
		{
			new_symbol = symbol;
		}
		else
		{
			symbol_table.push_back(symbol);
		}
	}

	void copy_symbol_table_from_parent(std::vector<std::shared_ptr<Symbol>> table)
	{
		symbol_table = table;
	}

public:
	virtual Node_type get_type() = 0;

	
};

#endif