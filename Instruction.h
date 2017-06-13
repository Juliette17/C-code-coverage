#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Assignement;
class Var_declaration;
class Scanf;
class Expression;
class Return_statement;
class Loop_stop;

class Instruction : public Node {

private:
	std::shared_ptr<Expression> expression;
	std::shared_ptr<Assignement> assignement;
	std::shared_ptr<Var_declaration> declaration;
	std::shared_ptr<Scanf> scanf_;
	std::shared_ptr<Return_statement> return_stat;
	std::shared_ptr<Loop_stop> loop_stop;
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
	void set_return(std::shared_ptr<Return_statement> r) { return_stat = r; }
	void set_loop_stop(std::shared_ptr<Loop_stop> ls) { loop_stop = ls; }
	std::shared_ptr<Assignement> get_assignement() { return assignement; }
	std::shared_ptr<Var_declaration> get_declaration() { return declaration; }
	std::shared_ptr<Scanf> get_scanf() { return scanf_; }
	char get_type(char x) {
		if (loop_stop != nullptr)
			return 'l';
		if (return_stat != nullptr)
			return 'r';
		if (scanf_ != nullptr)
			return 's';
		if (declaration != nullptr)
			return 'd';
		if (assignement != nullptr)
			return 'a';
		if (expression != nullptr)
			return 'e';
		else
			return 0;

	}

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