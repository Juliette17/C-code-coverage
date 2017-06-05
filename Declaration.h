#ifndef DECLARATION_H
#define DECLARATION_H

#include "Libraries.h"


class Var_declaration : public Node {
private:
	std::shared_ptr<Variable> variable;
	std::shared_ptr<Assignement> assignement;
public:
	Node_type get_type() {
		return Node_type::DECLARATION;
	}
	Var_declaration() : variable(nullptr), assignement(nullptr) {}
	void set_variable(std::shared_ptr<Variable> variable) { this->variable = variable; }
	//void set_assigned(std::shared_ptr<Assigned> value) { this->assignement = value; }
	void set_assignement(std::shared_ptr<Assignement> assignement) { this->assignement = assignement; }
	std::shared_ptr<Variable> get_variable() { return variable; }
	std::shared_ptr<Assignement> get_assignement() { return assignement; }
};

#endif
