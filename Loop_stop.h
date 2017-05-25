#ifndef LOOP_STOP_H
#define LOOP_STOP_H

class Loop_stop : public Node {
	Token token;
public:
	Node_type get_type() {
		return Node_type::LOOP_STOP;
	}
	Loop_stop(Token token) { this->token = token; }
};

#endif