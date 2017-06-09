#ifndef CONDITION_H
#define CONDITION_H

#include "Operator.h"
#include "Node.h"


class Condition : public Node {
public:
	//virtual std::shared_ptr<Condition> get_condition();
	Node_type get_type() {
		return Node_type::CONDITION;
	}
};

class Condition_complex : public Condition
{
	std::shared_ptr<Operator> operation; //always 1 (and, or)
	std::shared_ptr<Condition> left_condition;
	std::shared_ptr<Condition> right_condition;

public:
	Node_type get_type() {
		return Node_type::CONDITION;
	}

	Condition_complex(std::shared_ptr<Operator> op = nullptr, std::shared_ptr<Condition> left = nullptr, std::shared_ptr<Condition> right = nullptr)
	{
		this->operation = op;
		left_condition = left;
		right_condition = right;
	}
	//std::shared_ptr<Condition> get_condition() { return std::make_shared<Condition>(this); }
};

#endif