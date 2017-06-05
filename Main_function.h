#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "Libraries.h"


class Main_function : public Block {

public:
	Node_type get_type() {
		return Node_type::MAIN_FUNCTION;
	}

};


#endif //main