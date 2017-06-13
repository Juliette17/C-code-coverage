#ifndef NODE_H
#define NODE_H

#include <memory>
#include <string>


class Node {

public:
	enum class Node_type {
		PROGRAM, //0
		MAIN_FUNCTION, //1
		DEFINE, //2
		INCLUDE, //3
		WHILE_STATEMENT, //4
		IF_STATEMENT, //5
		ELSE_BLOCK, //6
		CONDITION, //7
		RETURN, //8
		LOOP_STOP, //CONTINUE AND BREAK //9
		DECLARATION, //VARIABLE DECLARATION //10
		ASSIGNEMENT, //11
		ASSIGNED, //12
		VARIABLE, //13
		OPERATOR, //14
		EXPRESSION, //15
		INSTRUCTION, //16
		COMMENT, //17
		SCANF, //18
		SCANF_PARAMETER //19
	};

	virtual Node_type get_type() = 0;
	virtual std::vector < std::shared_ptr<Node>> get_children() { std::vector < std::shared_ptr<Node>> children; return children; }
	//virtual std::shared_ptr<Node> get_parent() = 0;

};


#endif //NODE