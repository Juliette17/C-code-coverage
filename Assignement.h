#ifndef ASSIGNEMENT_H
#define ASSIGNEMENT_H

#include "Node.h"
#include "Variable.h"
#include <memory>

class Assignement : public Node {

private:
	std::shared_ptr<Variable> left_operand;
	std::shared_ptr<Expression> right_operand;

public:
	Node_type get_type() {
		return Node_type::ASSIGNEMENT;
	}
	void set_left(std::shared_ptr<Variable> var) { left_operand = var; }
	void set_right(std::shared_ptr<Expression> assigned) { right_operand = assigned; }

	std::shared_ptr<Variable> get_left() { return left_operand; }
	std::shared_ptr<Expression> get_right() { return right_operand; }
	virtual std::vector < std::shared_ptr<Node>> get_children() 
	{
		std::vector<std::shared_ptr<Node>> children;
		children.push_back(left_operand);
		children.push_back(std::dynamic_pointer_cast<Node>(right_operand));
		return children;
	}
};

#endif //assignement