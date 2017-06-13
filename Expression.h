#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include "Assigned.h"
#include "Condition.h"
#include "Operator.h"
class Variable;

class Expression :  public Condition {

private:
	std::shared_ptr<Operator> operation; 
	std::shared_ptr<Expression> left_operand;
	std::shared_ptr<Expression> right_operand;
	std::shared_ptr<Variable> variable;
	Identifier_type type; //int, char etc
	bool has_value;
	
public:
	Node_type get_type() {
		return Node_type::EXPRESSION;
	}
	Expression(std::shared_ptr<Operator> op = nullptr, std::shared_ptr<Expression> left = nullptr, std::shared_ptr<Expression> right = nullptr, Identifier_type type = Identifier_type::DOUBLE_ID, bool has_value = false)
	{
		this->type = type;
		this->operation = op;
		left_operand = left;
		right_operand = right;
		this->has_value = has_value;
		variable = nullptr;
	}

	Expression(std::shared_ptr<Variable> var)
	{
		this->type = var->get_assigned_type();
		this->operation = nullptr;
		left_operand = nullptr;
		right_operand = nullptr;
		variable = var;
		if (var->has_valuee())
		{
			this->has_value = true;
		}
			
	}

	virtual std::vector < std::shared_ptr<Node>> get_children()
	{
		std::vector<std::shared_ptr<Node>> children;
		children.push_back(operation);

		children.push_back(std::dynamic_pointer_cast<Node>(left_operand));
		children.push_back(std::dynamic_pointer_cast<Node>(right_operand));
		children.push_back(variable);
		return children;
	}
	//Expression(Expression& e) {}

	//std::shared_ptr<Condition> get_condition() { return std::make_shared<Expression>(this->operation, this->left_operand, this->right_operand); }
	Identifier_type get_operand_type() { return type; }
	std::shared_ptr<Expression> get_left() { return left_operand; }
	std::shared_ptr<Expression> get_right() { return right_operand; }
	std::shared_ptr<Operator> get_operation() { return operation; }
	std::shared_ptr<Variable> get_variable() { return variable; }
	void set_left(std::shared_ptr<Expression> a) { left_operand = a; }
	void set_right(std::shared_ptr<Expression> a) { right_operand = a; }
	void set_operation(std::shared_ptr<Operator> operation) { this->operation = operation; }
	Identifier_type get_assigned_type() { return type; }
	void set_assigned_type(Identifier_type type) { this->type = type; }
	bool has_valuee() { return has_value; }
	void set_has_value(bool has) { has_value = has; }
};

#endif //expression