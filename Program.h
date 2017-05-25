#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <vector>
#include "Node.h"
#include "Define.h"
#include "Main_function.h"
#include "Declaration.h"
#include "Include.h"


class Program : public Node {

private:
	std::vector<std::shared_ptr<Define>> defines;
	std::shared_ptr<Include> include;
	std::shared_ptr<Main_function> main;
	std::vector<std::shared_ptr<Var_declaration>> declarations;

public:
	Program() : include(nullptr), main(nullptr) {}

	Node_type get_type() { return Node_type::PROGRAM; }
	void add_to_defines(std::shared_ptr<Define> def) {
		defines.push_back(def);
	}
	void add_include(std::shared_ptr<Include> include)
	{
		this->include = include;
	}
	void add_main(std::shared_ptr<Main_function> main)
	{
		this->main = main;
	}
	void add_declaration(std::shared_ptr<Var_declaration> dec)
	{
		declarations.push_back(dec);
	}
	std::vector<std::shared_ptr<Define>> get_defines() { return defines; }
	std::shared_ptr<Include> get_include() { return include;  }
	std::shared_ptr<Main_function> get_main() { return main; }
	std::vector<std::shared_ptr<Var_declaration>> get_declarations() { return declarations; }

};

#endif //program