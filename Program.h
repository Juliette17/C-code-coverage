#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <vector>
#include "Libraries.h"


class Program : public Node {

private:
	std::vector<std::shared_ptr<Define>> defines;
	std::shared_ptr<Include> include;
	std::shared_ptr<Main_function> main;
	std::vector<std::shared_ptr<Var_declaration>> declarations;
	std::vector<std::shared_ptr<Comment>> comments;
	std::vector<std::shared_ptr<Symbol>> symbol_table;

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
	void add_comment(std::shared_ptr<Comment> com)
	{
		comments.push_back(com);
	}
	void add_declaration(std::shared_ptr<Var_declaration> dec)
	{
		declarations.push_back(dec);
	}
	std::vector<std::shared_ptr<Define>> get_defines() { return defines; }
	std::shared_ptr<Include> get_include() { return include;  }
	std::shared_ptr<Main_function> get_main() { return main; }
	std::vector<std::shared_ptr<Var_declaration>> get_declarations() { return declarations; }

	
	std::shared_ptr<Symbol> find_in_symbol_table(std::shared_ptr<Symbol> symbol)
	{
		for (auto& s : symbol_table)
		{
			if (s->get_name() == symbol->get_name())
			{
				return s;
			}
		}
		return nullptr;
	}

	void add_to_symbol_table(std::shared_ptr<Symbol> symbol)
	{
		std::shared_ptr<Symbol> new_symbol = find_in_symbol_table(symbol);
		if (new_symbol != nullptr)
		{
			new_symbol = symbol;
		}
		else
		{
			symbol_table.push_back(symbol);
		}
	}


};

#endif //program