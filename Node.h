#ifndef NODE_H
#define NODE_H

#include <memory>
#include <string>


class Node {

public:
	enum class Node_type {
		PROGRAM,
		MAIN_FUNCTION,
		DEFINE,
		INCLUDE,
		WHILE_STATEMENT,
		IF_STATEMENT,
		ELSE_BLOCK,
		CONDITION,
		RETURN,
		LOOP_STOP, //CONTINUE AND BREAK
		DECLARATION, //VARIABLE DECLARATION
		ASSIGNEMENT,
		ASSIGNED,
		VARIABLE,
		OPERATOR,
		EXPRESSION,
		INSTRUCTION,
		COMMENT,
		SCANF,
		SCANF_PARAMETER
	};

	virtual Node_type get_type() = 0;
	virtual std::vector < std::shared_ptr<Node>> get_children() { std::vector < std::shared_ptr<Node>> children; return children; }
	//virtual std::shared_ptr<Node> get_parent() = 0;

};


#endif //NODE