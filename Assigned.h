#ifndef ASSIGNED_H
#define ASSIGNED_H

#include "Token_type.h"
#include "Node.h"

class Assigned : virtual public Node {

protected:
	Identifier_type type; //int, char etc
	bool has_value;

public:
	virtual Node_type get_type() = 0;
	Identifier_type get_assigned_type() { return type; }
	void set_assigned_type(Identifier_type type) { this->type = type; }
	bool has_valuee() { return has_value; }
	void set_has_value(bool has) { has_value = has; }
};

#endif //assigned_h