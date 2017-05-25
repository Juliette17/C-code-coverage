#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Node.h"
#include "Expression.h"
#include "Declaration.h"
#include "Scanf.h"

class Instruction : public Node {

private:
	std::shared_ptr<Expression> expression;
	std::shared_ptr<Assignement> assignement;
	std::shared_ptr<Var_declaration> declaration;
	std::shared_ptr<Scanf> scanf;
	std::vector<Token> tokens;
public:
	Node_type get_type() {
		return Node_type::INSTRUCTION;
	}

	void set_expression(std::shared_ptr<Expression> expression) {
		this->expression = expression;
	}
	void set_assignement(std::shared_ptr<Assignement> a) { assignement = a; }
	void set_declaration(std::shared_ptr<Var_declaration> declar) { declaration = declar; }
	void set_scanf(std::shared_ptr<Scanf> s) { scanf = s; }

};


#endif //instruction