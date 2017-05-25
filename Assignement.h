#ifndef ASSIGNEMENT_H
#define ASSIGNEMENT_H

#include "Node.h"
#include "Variable.h"
#include "Assigned.h"
#include <memory>

class Assignement : public Node {

private:
	std::shared_ptr<Variable> left_operand;
	std::shared_ptr<Assigned> right_operand;

public:
	Node_type get_type() {
		return Node_type::ASSIGNEMENT;
	}
	void set_left(std::shared_ptr<Variable> var) { left_operand = var; }
	void set_right(std::shared_ptr<Assigned> assigned) { right_operand = assigned; }
};

#endif //assignement