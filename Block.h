#ifndef BLOCK_H
#define BLOCK_H

#include "Node.h"
#include "Instruction.h"
#include "Loop_stop.h"
#include "Comment.h"
#include "Return_statement.h"
#include <vector>

class Block : public Node {

protected:
	std::vector<std::shared_ptr<Instruction>> instructions;
	std::vector<std::shared_ptr<Block>> blocks;
	std::vector<std::shared_ptr<Comment>> comments;
	std::vector<std::shared_ptr<Return_statement>> returns;
	std::vector<std::shared_ptr<Loop_stop>> loop_stops;
	std::shared_ptr<Condition> condition;

public:
	std::vector<std::shared_ptr<Instruction>> get_instructions() { return instructions; }
	std::vector<std::shared_ptr<Block>> get_blocks() { return blocks; }
	std::vector<std::shared_ptr<Comment>> get_comments() { return comments; }
	std::vector<std::shared_ptr<Return_statement>> get_returns() { return returns; }

	void add_to_instructions(std::shared_ptr<Instruction> instruction) { this->instructions.push_back(instruction); }
	void add_to_blocks(std::shared_ptr<Block> block) { this->blocks.push_back(block); }
	void add_to_comments(std::shared_ptr<Comment> comment) { this->comments.push_back(comment); }
	void add_to_returns(std::shared_ptr<Return_statement> ret) { this->returns.push_back(ret); }

	std::vector<std::shared_ptr<Loop_stop>> get_loop_stops() { return loop_stops; }
	void add_loop_stops(std::shared_ptr<Loop_stop> ls) { loop_stops.push_back(ls); }

public:
	virtual Node_type get_type() = 0;

	std::shared_ptr<Condition> get_condition() { return condition; }
	void set_condition(std::shared_ptr<Condition> cond) { this->condition = cond; }
};

#endif