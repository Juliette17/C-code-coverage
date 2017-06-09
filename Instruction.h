#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Assignement;
class Var_declaration;
class Scanf;
class Expression;

class Instruction : public Node {

private:
	std::shared_ptr<Expression> expression;
	std::shared_ptr<Assignement> assignement;
	std::shared_ptr<Var_declaration> declaration;
	std::shared_ptr<Scanf> scanf_;
	//std::vector<Token> tokens;
public:
	Node_type get_type() {
		return Node_type::INSTRUCTION;
	}
	Instruction() : expression(nullptr), assignement(nullptr), declaration(nullptr), scanf_(nullptr) {}

	void set_expression(std::shared_ptr<Expression> expression) {
		this->expression = expression;
	}
	void set_assignement(std::shared_ptr<Assignement> a) { assignement = a; }
	void set_declaration(std::shared_ptr<Var_declaration> declar) { declaration = declar; }
	void set_scanf(std::shared_ptr<Scanf> s) { scanf_ = s; }

	std::shared_ptr<Scanf> get_scanf_() { return scanf_; }

	virtual std::vector < std::shared_ptr<Node>> get_children()
	{
		std::vector<std::shared_ptr<Node>> children;
		std::shared_ptr<Node> temp = std::dynamic_pointer_cast<Node> (expression);
		children.push_back(temp);
		children.push_back(std::dynamic_pointer_cast<Node> (assignement));
		children.push_back(std::dynamic_pointer_cast<Node> (declaration));
		children.push_back(std::dynamic_pointer_cast<Node> (scanf_));
		return children;
	}

};


#endif //instruction