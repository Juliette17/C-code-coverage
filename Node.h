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

};


#include "Assigned.h"
#include "Assignement.h"
#include "Block.h"
#include "Condition.h"
#include "Declaration.h"
#include "Define.h"
#include "Defined_tokens.h"
#include "Error_handler.h"
#include "Expression.h"
#include "If_statement.h"
#include "Instruction.h"
#include "Loop_stop.h"
#include "Main_function.h"
#include "Operator.h"
#include "Output_handler.h"
#include "Program.h"
#include "Symbol.h"
#include "Token.h"
#include "Token_type.h"
#include "Variable.h"
#include "While_statement.h"



#endif //NODE