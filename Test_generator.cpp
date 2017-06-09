#include "Test_generator.h"

void Test_generator::add_to_symbol_table(std::shared_ptr<Symbol> s)
{
	symbol_table.push_back(s);
}
void Test_generator::add_to_scanfs(std::shared_ptr<Scanf> s)
{
	scanfs.push_back(s);

}
void Test_generator::clear_symbol_table()
{
	while (symbol_table.size() > 0)
	{
		symbol_table.pop_back();
	}
}
void Test_generator::clear_scanfs()
{
	while (scanfs.size() > 0)
	{
		scanfs.pop_back();
	}
}

bool Test_generator::is_rel_operator(Token_type type)
{
	if (rel_operators.find(type) != rel_operators.end()) return true;
	else return false;
}

bool Test_generator::is_conjunction_operator(Token_type type)
{
	if (type == Token_type::AND || type == Token_type::OR) return true;

	else return false;
}

void Test_generator::init_symbol_table_and_scanfs()
{
	while (symbol_table.size() > 0)
	{
		symbol_table.pop_back();
	}
	std::shared_ptr<Symbol> temp_symbol;
	for (int i = 0; i < parser.get_symbol_table().size(); ++i)
	{
		if (parser.get_symbol_table()[i]->get_type() == Identifier_type::INT_ID)
		{
			temp_symbol = std::make_shared<Integer_symbol>(parser.get_symbol_table()[i]->get_name());
		}
		else if (parser.get_symbol_table()[i]->get_type() == Identifier_type::FLOAT_ID)
		{
			temp_symbol = std::make_shared<Float_symbol>(parser.get_symbol_table()[i]->get_name());
		}
		else if (parser.get_symbol_table()[i]->get_type() == Identifier_type::DOUBLE_ID)
		{
			temp_symbol = std::make_shared<Double_symbol>(parser.get_symbol_table()[i]->get_name());
		}
		else if (parser.get_symbol_table()[i]->get_type() == Identifier_type::CHAR_ID)
		{
			temp_symbol = std::make_shared<Character_symbol>(parser.get_symbol_table()[i]->get_name());
		}
		if (parser.get_symbol_table()[i]->has_valuee())
		{
			double d = 1.0;
			temp_symbol->set_value(parser.get_symbol_table()[i]->get_value(d));
		}		
		symbol_table.push_back(temp_symbol);
	}
	while (scanfs.size() > 0)
	{
		scanfs.pop_back();
	}
	for (int i = 0; i < parser.get_tree_root()->get_main()->get_instructions().size(); ++i)
	{
		if (parser.get_tree_root()->get_main()->get_instructions()[i]->get_scanf_() != nullptr)
			scanfs.push_back(parser.get_tree_root()->get_main()->get_instructions()[i]->get_scanf_());
	}
}



void Test_generator::run()
{
	int result = 0;
	for (int i = 0; i < executing_blocks.size(); ++i)
	{
		result = calculate_condition(executing_blocks[i].scope->get_condition());
		if (result != 0)
		{
			execute_block_on_condition_true(executing_blocks[i].scope);
		}
	}
}

void Test_generator::init()
{
	std::shared_ptr<Program> root = get_tree_root();
	std::shared_ptr<Block> main = root->get_main();
	std::vector<std::shared_ptr<Block>> main_scope;
	std::vector<std::shared_ptr<Block>> parents;
	Executing_block eb(main, false, -1, parents);
	init_executing_blocks(eb);
	init_symbol_table_and_scanfs();
	std::cout << "executing blocks " << executing_blocks.size() << std::endl;
	Output_handler::show_symbol_table(symbol_table);
	std::cout << "scanfs " << scanfs.size() << std::endl;
	/*main_scope.push_back(main);
	add_to_scopes(main_scope);
	analyze_scopes(main_scope);
	analyze_conditions();
	set_default_value_of_scanf_parameters();
	check_conditions(); //and add tests*/
}

void Test_generator::init_executing_blocks(Executing_block executing_block)
{
	/*while (executing_blocks.size() > 0)
	{
		executing_blocks.pop_back();
	}*/
	for (int i = 0; i < executing_block.scope->get_blocks().size(); ++i)
	{
		std::vector < std::shared_ptr<Block>> parents = executing_block.parents;
		if (executing_block.scope->get_type() != Node::Node_type::MAIN_FUNCTION)
			parents.push_back(executing_block.scope);

		Executing_block eb(executing_block.scope->get_blocks()[i], false, -1, parents);
		executing_blocks.push_back(eb);
		init_executing_blocks(eb);
	}	
}

void Test_generator::execute_block_on_condition_true(std::shared_ptr<Block> scope)
{

}

double Test_generator::calculate_condition(std::shared_ptr<Expression> condition)
{
	return 1.0;
}


















void Test_generator::analyze_scopes(std::vector<std::shared_ptr<Block>> scope_for_now)
{
	std::vector<std::shared_ptr<Block>> children = scope_for_now[scope_for_now.size() - 1]->get_blocks();
	for (int i = 0; i < children.size(); ++i)
	{
		scope_for_now.push_back(children[i]);
		add_to_scopes(scope_for_now);
		analyze_scopes(scope_for_now);
		scope_for_now.pop_back();
	}
}
void Test_generator::analyze_conditions()
{
	int number_of_vectors = scopes.size();
	
	for (int i = 1; i < number_of_vectors; ++i)
	{
		std::shared_ptr<Block> scope = scopes[i][scopes[i].size() - 1];
		for (int j = 1; j < scopes[i].size(); ++j)
		{
			scope->add_to_complex_conditions(scopes[i][j]->get_condition());
			//scope->add_to_parents(scopes[i][j]);
		}
	}
}

void Test_generator::check_conditions()
{
	int number_of_vectors = scopes.size();
	bool temp_cond_val;
	for (int i = 1; i < number_of_vectors; ++i) //i = 0 is main
	{
		std::shared_ptr<Block> scope = scopes[i][scopes[i].size() - 1];
		for (int j = 1; j < scopes[i].size(); ++j)
		{
			 temp_cond_val = check_one_condition(scope);
			 if (temp_cond_val == false)
				 break;
		}
		condition_values.push_back(temp_cond_val);
	}
}

bool Test_generator::check_one_condition(std::shared_ptr<Block> scope)
{
	std::vector < std::shared_ptr<Expression >> complex_cond = scope->get_complex_conditions();
	double value = 0;
	for (int i = 0; i < complex_cond.size(); ++i)
	{
		value = portion_to_single_conditions(complex_cond[i], scope);
		if (value = false)
			return false;
	}
	return true;
}

double Test_generator::portion_to_single_conditions(std::shared_ptr<Expression> temp_cond, std::shared_ptr<Block> scope)
{
	std::shared_ptr<Variable> var = temp_cond->get_variable();
	if (var != nullptr)
	{
		//scope->find_in_symbol_table(var->get_name());
		if (var->has_valuee())
		{
			return var->get_value();
		}
		if (parser.get_all_scanfs_in_program().size())
		{
			std::vector<std::shared_ptr<Scanf>> scanfs = parser.get_all_scanfs_in_program();
			for (int i = scanfs.size()-1; i >= 0; --i) //get the closest scanf
			{
				std::shared_ptr<Scanf_parameter> p = scanfs[i]->get_parameter(var->get_name());
				//if (p != nullptr)

			}
		}
	}

	Token_type oper =  temp_cond->get_operation()->get_operator_type();
	//if ()
	if (is_conjunction_operator(oper))
	{
		std::cout << "conjunction_operator" << std::endl;
		if (oper == Token_type::AND)
		{
			std::cout << "and" << std::endl;
		}
		else
			std::cout << "or" << std::endl;
		portion_to_single_conditions(temp_cond->get_left(), scope);
		portion_to_single_conditions(temp_cond->get_right(), scope);

	}

	if (is_rel_operator(oper))
	{
		std::cout << "rel_operator" << std::endl;
		if (temp_cond->get_left() == nullptr || temp_cond->get_right() == nullptr)
			std::cout << "nullptr" << std::endl;
		std::shared_ptr<Variable> var1 = temp_cond->get_left()->get_variable();
		std::shared_ptr<Variable> var2 = temp_cond->get_right()->get_variable();
		if (var1 != nullptr && var2 != nullptr) //ok! stop going further
		{
			std::cout << "obie nie nullptr" << std::endl;
			if (var1->has_valuee() && var2->has_valuee())
			{
				std::cout << "obie maja wartosc" << var1->get_name() << var2->get_name() << std::endl;

				/*switch (temp_cond->get_operation()->get_operator_type())
				{
				case (Token_type::EQUALITY) :
					if (var1->get_value() == var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;

				case (Token_type::INEQUALITY) :
					if (var1->get_value() != var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;

				case(Token_type::GREATER) :
					if (var1->get_value() > var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;

				case(Token_type::GREATER_OR_EQUAL) :
					if (var1->get_value() >= var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;

				case(Token_type::LESS) :
					if (var1->get_value() < var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;

				case(Token_type::LESS_OR_EQUAL) :
					if (var1->get_value() <= var2->get_value())
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
					else
						scope->add_to_condition_values(std::make_pair(temp_cond, false));
					break;
				default:
					break;

				}*/
			}
			else
			{
				if (var1->has_valuee() && !var2->has_valuee())
				{
					std::cout << "var1 ma wwartosc" << std::endl;
				}
					
				if (var2->has_valuee() && !var1->has_valuee())
				{
					std::cout << "var2 ma wwartosc" << std::endl;
					std::shared_ptr<Symbol> found_symbol;
					std::shared_ptr<Scanf> scanf;
					found_symbol = scope->find_in_symbol_table(var1->get_name());
					scanf = found_symbol->get_scanfs()[found_symbol->get_scanfs().size() - 1];
					/*switch (temp_cond->get_operation()->get_operator_type())
					{
					case (Token_type::EQUALITY) :
						set_value_of_scanf_parameter(scanf, var1->get_name(), var2->get_value());
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
						break;

					case (Token_type::INEQUALITY) :
					case (Token_type::GREATER) :
					case (Token_type::GREATER_OR_EQUAL) :
						set_value_of_scanf_parameter(scanf, var1->get_name(), var2->get_value()+1);
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
						break;

					case (Token_type::LESS) :
					case (Token_type::LESS_OR_EQUAL) :
						set_value_of_scanf_parameter(scanf, var1->get_name(), var2->get_value() - 1);
						scope->add_to_condition_values(std::make_pair(temp_cond, true));
						break;
					default:
						break;
					}*/
				}
					
				if (!var1->has_valuee() && !var2->has_valuee())
				{
					std::cout << "obie nie maja wartosci" << std::endl;
				}
					
			}
		}
		else
		{
			if (var1 == nullptr)
			{
				if (temp_cond->get_left()->get_operation() == nullptr && temp_cond->get_left()->get_left() == nullptr && temp_cond->get_left()->get_right() == nullptr && temp_cond->get_left()->get_variable() == nullptr)
					std::cout << "wszystkie null" << std::endl;
					std::cout << "left null" << std::endl;
				portion_to_single_conditions(temp_cond->get_left(), scope);

			}
			if (var2 == nullptr)
			{
				std::cout << "right null" << std::endl;
				portion_to_single_conditions(temp_cond->get_right(), scope);
			}
		}
		//return temp_cond;
	}
	/*std::shared_ptr<Variable> var = temp_cond->get_variable();
	if (var == nullptr)
	{
		portion_to_single_conditions(temp_cond->get_left(), scope);
		if (temp_cond->get_operation() != nullptr)
		{
		}*/
	
}

void Test_generator::set_value_of_scanf_parameter(std::shared_ptr<Scanf> scanf, std::string name, double value)
{
	std::shared_ptr<Scanf_parameter> param = scanf->get_parameter(name);
	param->set_value(value);
}

void Test_generator::set_default_value_of_scanf_parameters()
{
	std::vector<std::shared_ptr<Scanf>> scanfs = parser.get_all_scanfs_in_program();
	for (int i = 0; i < parser.get_all_scanfs_in_program().size(); ++i)
	{
		std::shared_ptr<Scanf> scanf = scanfs[i];
		for (auto& param : scanf->get_parameters())
		{
			param->set_value(0);
		}
	}
}




