#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include "Node.h"
#include "Operator.h"
#include "Condition.h"

class Expression : public Assigned, public Condition {

private:
	std::shared_ptr<Operator> operation; 
	std::shared_ptr<Assigned> left_operand;
	std::shared_ptr<Assigned> right_operand;
	
public:
	Node_type get_type() {
		return Node_type::EXPRESSION;
	}
	Expression(std::shared_ptr<Operator> op = nullptr, std::shared_ptr<Assigned> left = nullptr, std::shared_ptr<Assigned> right = nullptr, Identifier_type type = Identifier_type::DOUBLE_ID, bool has_value = false)
	{
		this->type = type;
		this->operation = op;
		left_operand = left;
		right_operand = right;
		this->has_value = has_value;
	}

	Identifier_type get_operand_type() { return type; }
	std::shared_ptr<Assigned> get_left() { return left_operand; }
	std::shared_ptr<Assigned> get_right() { return left_operand; }
	std::shared_ptr<Operator> get_operation() { return operation; }
	void set_left(std::shared_ptr<Assigned> a) { left_operand = a; }
	void set_right(std::shared_ptr<Assigned> a) { right_operand = a; }
	void set_operation(std::shared_ptr<Operator> operation) { this->operation = operation; }
};

#endif //expression