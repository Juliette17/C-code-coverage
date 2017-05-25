#ifndef DEFINE_H
#define DEFINE_H

#include "Node.h"
#include "Variable.h"
#include <memory>

class Define : public Node {

private:
	std::shared_ptr<Variable> constant;

public:
	Node_type get_type() {
		return Node_type::DEFINE;
	}
	std::shared_ptr<Variable> get_constant() { return constant; }
	void set_constant(std::shared_ptr<Variable> constant) { this->constant = constant; }
};

#endif