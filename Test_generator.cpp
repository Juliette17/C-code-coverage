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
	while (!executing_blocks[0]->executed) // whole main
	{
		execute_block_on_condition_true(executing_blocks[0]);

	}
		

	/*result = calculate_condition(executing_blocks.scope->get_condition());
	if (result != 0)
	{
		execute_block_on_condition_true(executing_blocks[i].scope);
	}*/
	
}

void Test_generator::init()
{
	std::shared_ptr<Program> root = get_tree_root();
	std::shared_ptr<Block> main = root->get_main();
	//std::vector<std::shared_ptr<Block>> main_scope;
	std::vector<std::shared_ptr<Block>> parents;
	init_symbol_table_and_scanfs(); //from global scope
	std::shared_ptr<Executing_block> eb = std::make_shared<Executing_block>(main, false, -1, parents, symbol_table, scanfs);
	executing_blocks.push_back(eb);
	init_executing_blocks(eb);
	std::cout << "executing blocks " << executing_blocks.size() << std::endl;
	Output_handler::show_symbol_table(symbol_table);
	std::cout << "scanfs " << scanfs.size() << std::endl; //from global scope - of course 0
	std::cout << "executing blocks" << std::endl;
	for (int i = 0; i < executing_blocks.size(); ++i)
	{
		std::cout << executing_blocks[i]->scope->get_type() << std::endl;
		std::cout << executing_blocks[i]->parents.size() << std::endl;
		for (int j = 0; j < executing_blocks[i]->parents.size(); ++j)
		{
			std::cout << '\t' << executing_blocks[i]->parents[j]->get_type() << std::endl;
		}
		
	}
	/*main_scope.push_back(main);
	add_to_scopes(main_scope);
	analyze_scopes(main_scope);
	analyze_conditions();
	set_default_value_of_scanf_parameters();
	check_conditions(); //and add tests*/
}

void Test_generator::init_executing_blocks(std::shared_ptr<Executing_block> executing_block)
{
	/*while (executing_blocks.size() > 0)
	{
		executing_blocks.pop_back();
	}*/
	for (int i = 0; i < executing_block->scope->get_blocks().size(); ++i)
	{
		std::vector < std::shared_ptr<Block>> parents; 
		parents.insert(parents.begin(), executing_block->parents.begin(), executing_block->parents.end());
		if (executing_block->scope->get_type() != Node::Node_type::MAIN_FUNCTION)
			parents.push_back(executing_block->scope);

		std::shared_ptr<Executing_block> eb = std::make_shared<Executing_block>(executing_block->scope->get_blocks()[i], false, -1, parents, symbol_table, scanfs);
		executing_blocks.push_back(eb);
		init_executing_blocks(eb);
	}	
}


//////////////////////////////////FINISH THIS///////////////////////////////
//do something with loop stops - it doesnt work as it should.....
int Test_generator::execute_block_on_condition_true(std::shared_ptr<Executing_block> eb)
{
	int condition_value = 0;
	std::shared_ptr<Block> scope = eb->scope;
	char instruction_result = 0;
	bool loop_stop = false;
	int execute_block_result = 0;
	//wyczyscic symbol table i dodawac po symbolu przy deklaracji
	std::cout << "symbol table" << scope->get_symbol_table().size() << std::endl;
	for (int i = 0; i < scope->get_children().size(); ++i)
	{
		if (scope->get_children()[i]->get_type() == Node::Node_type::INSTRUCTION)
		{
			std::shared_ptr<Instruction> instr = std::dynamic_pointer_cast<Instruction>(scope->get_children()[i]);
			instruction_result = accept_instruction(instr, eb);
			if ( instruction_result == 'r')
				return 1;
			if (instruction_result == 'l' && eb->scope->get_type() == Node::Node_type::WHILE_STATEMENT)
				return 2;
			if (instruction_result == 'l' && eb->scope->get_type() != Node::Node_type::WHILE_STATEMENT)
				loop_stop = true;	
		}
		else 
		{
			//wrong with loop stop -----> stop executing when loop_stop
			std::shared_ptr<Block> b = std::dynamic_pointer_cast<Block>(scope->get_children()[i]);
			std::shared_ptr<Executing_block> new_eb = find_executing_block(b);
			new_eb->symbol_table = eb->symbol_table;
			for (auto&s : eb->symbol_table)
			{
				std::cout << "scope" << eb->scope->get_type() << std::endl;
				std::cout << "s " << s->get_name() << s->get_value(1.5) << std::endl;
			}

			if (new_eb->executed == false)
			{
				condition_value = calculate_expression(new_eb, b->get_condition(), false, true, nullptr);
				if (condition_value != 0)
				{ 
					std::cout << "ok " << condition_value << std::endl;
					execute_block_result = execute_block_on_condition_true(new_eb);
					if (execute_block_result == 1)
						return 1;
					if (execute_block_result == 3 && eb->scope->get_type() == Node::Node_type::WHILE_STATEMENT)
						return 2;
					if (execute_block_result == 3 && eb->scope->get_type() != Node::Node_type::WHILE_STATEMENT)
						loop_stop = true;
					if (execute_block_result == 3 && eb->scope->get_type() == Node::Node_type::MAIN_FUNCTION)
					{
						//Error_handler::loop_stop_with_no_while
						return -1;
					}
				}
				else
				{
					return -1; //false condition
				}
			}
			else
			{
				continue;
			}
		}
		eb->last_executed_instruction++;
		std::cout << "child " << scope->get_children()[i]->get_type() << std::endl;
	}
	eb->executed = true;
	if (loop_stop == true)
		return 3;
	return 0; // if ok, 1 if return, 2 if loop stop of this scope, 3 if loop_stop of outer_scope, -1 wrong condition
}

/*
returns:
'r' if return
'l' if loop stop
'e' if expression
'a' if assignement
'd' if declaration
's' if scanf
0 if empty
*/
char Test_generator::accept_instruction(std::shared_ptr<Instruction> instr, std::shared_ptr<Executing_block> eb)
{
	char type = instr->get_type('x');
	if (type == 'l')
	{
		return 'l';
	}
	if (type == 'r')
	{
		return 'r';
	}
	if (type == 's')
	{
		//add scanf to symbol table of executing block?
		eb->scanfs.push_back(instr->get_scanf());
		return 's';
	}
	if (type == 'd')
	{
		std::shared_ptr<Symbol> new_symbol;
		std::shared_ptr<Variable> var = instr->get_declaration()->get_variable();
		if (var->get_assigned_type() == Identifier_type::CHAR_ID)
			new_symbol = std::make_shared<Character_symbol>(var->get_name(), var->get_assigned_type());
		else if (var->get_assigned_type() == Identifier_type::INT_ID)
			new_symbol = std::make_shared<Integer_symbol>(var->get_name(), var->get_assigned_type());
		else if (var->get_assigned_type() == Identifier_type::FLOAT_ID)
			new_symbol = std::make_shared<Float_symbol>(var->get_name(), var->get_assigned_type());
		else if (var->get_assigned_type() == Identifier_type::DOUBLE_ID)
			new_symbol = std::make_shared<Double_symbol>(var->get_name(), var->get_assigned_type());
	
		if (instr->get_declaration()->get_assignement() != nullptr && instr->get_declaration()->get_assignement()->get_right() != nullptr)
		{
			if (instr->get_declaration()->get_assignement()->get_right()->get_variable() != nullptr) //just variable
			{
				double v = instr->get_declaration()->get_assignement()->get_right()->get_variable()->get_value();
				new_symbol->set_value(v);
				std::shared_ptr<Symbol> found_symbol = find_in_symbol_table(eb, new_symbol->get_name());
				if (found_symbol != nullptr)
				{
					change_symbol_in_table(found_symbol, new_symbol, eb);
				}
				else
				{
					eb->symbol_table.push_back(new_symbol);
				}
				std::cout << new_symbol->get_name() << "  " << new_symbol->get_value() << std::endl;
			}
			else //expression 
			{
				double value = calculate_expression(eb, instr->get_declaration()->get_assignement()->get_right(), false, false, nullptr);
				new_symbol->set_value(value);
				std::shared_ptr<Symbol> found_symbol = find_in_symbol_table(eb, new_symbol->get_name());
				if (found_symbol != nullptr)
				{
					change_symbol_in_table(found_symbol, new_symbol, eb);
				}
				else
				{
					eb->symbol_table.push_back(new_symbol);
				}
				std::cout << new_symbol->get_name() << "  " << new_symbol->get_value() << std::endl;
			}
		}
		
		return 'd';
	}
	if (type == 'a')
	{	
		std::shared_ptr<Symbol> assigning_symbol;
		std::shared_ptr<Symbol> symbol = find_in_symbol_table(eb, instr->get_assignement()->get_left()->get_name());
		if (instr->get_assignement()->get_right()->get_variable() != nullptr)
			assigning_symbol = find_in_symbol_table(eb, instr->get_assignement()->get_right()->get_variable()->get_name());
		if (symbol != nullptr && assigning_symbol != nullptr)
		{
			double v = assigning_symbol->get_value(1.5);
			symbol->set_value(v);
			std::cout << symbol->get_name() << "  " << symbol->get_value() << std::endl;
		}
		else if (symbol == nullptr) //undeclared variable
			;
		else // symbol != nullptr, but expression on right
		{
			double v = calculate_expression(eb, instr->get_declaration()->get_assignement()->get_right(), false, false, nullptr);
			symbol->set_value(v);
		}

		return 'a';
	}
	if (type == 'e')
	{
		return 'e';
	}
	else
		return 0;
	return 0; // if empty
}

double Test_generator::calculate_expression(std::shared_ptr<Executing_block> eb, std::shared_ptr<Expression> expression, bool is_left, bool is_condition, std::shared_ptr<Expression> outer_expression)
{
	for (auto&s : eb->symbol_table)
	{
		std::cout << "scope" << eb->scope->get_type() << std::endl;
		std::cout << "s " << s->get_name() << s->get_value(1.5) << std::endl;
	}

	std::shared_ptr<Operator> op = expression->get_operation();
	if (op == nullptr)
	{
		
		if (expression->get_variable() != nullptr && expression->get_variable()->has_valuee()) // constant number?
		{
			std::cout << "var" << expression->get_variable()->get_value() << std::endl;
			return expression->get_variable()->get_value();
		}
		else if (expression->get_variable() != nullptr)
		{
			std::shared_ptr<Scanf_parameter> sp = in_scanfs(eb, expression->get_variable()->get_name());
			std::cout << expression->get_variable()->get_name() << std::endl;
			std::cout << eb->scanfs.size() << std::endl;
			if (sp != nullptr && is_condition && outer_expression != nullptr && outer_expression->get_operation() != nullptr)
			{
				switch (outer_expression->get_operation()->get_operator_type())
				{
					case (Token_type::EQUALITY) :
						if (is_left)
						{
							double value = calculate_expression(eb, outer_expression->get_right(), false, true, outer_expression);
							if (!sp->has_value)
								sp->set_value(value);
							else
								return 0;
						}
						else
						{
							double value = calculate_expression(eb, outer_expression->get_left(), true, true, outer_expression);
							sp->set_value(value);
						}
						break;
					case (Token_type::LESS) :
					case (Token_type::LESS_OR_EQUAL) :
						if (is_left)
						{
							double value = calculate_expression(eb, outer_expression->get_right(), false, true, outer_expression);
							if (sp->has_max_value)
							{
								sp->set_max_value(min(value, sp->get_max_value()));
							}
							else
								sp->set_max_value(value);
						}
						else
						{
							double value = calculate_expression(eb, outer_expression->get_left(), true, true, outer_expression);
							if (sp->has_min_value)
							{
								sp->set_min_value(max(value, sp->get_min_value()));
							}
							else
								sp->set_min_value(value);
								
						}
						break;
						
					case (Token_type::GREATER) :
					case (Token_type::GREATER_OR_EQUAL) :
						if (is_left)
						{
							double value = calculate_expression(eb, outer_expression->get_right(), false, true, outer_expression);
							if (sp->has_min_value)
							{
								sp->set_min_value(max(value, sp->get_min_value()));
							}
							else
								sp->set_min_value(value);
						}
						else
						{
							double value = calculate_expression(eb, outer_expression->get_left(), true, true, outer_expression);
							if (sp->has_max_value)
							{
								sp->set_max_value(min(value, sp->get_max_value()));
							}
							else
								sp->set_max_value(value);
						}
						break;
					case (Token_type::NEGATION) :
						if (!sp->has_value)
							sp->set_value(0);
						else
						return 0;
					default: //error
						Error_handler::uninitialised_variable(expression->get_variable()->get_name());
						return 0;
				}
			}
			else if (sp != nullptr && is_condition)
			{
				sp->add_prohibited(0);
				return 1;
			}
			else if (sp == nullptr)
			{
				std::shared_ptr<Symbol> found_s = find_in_symbol_table(eb, expression->get_variable()->get_name());
				if (found_s == nullptr || found_s->has_valuee() == false)
				{
					Error_handler::uninitialised_variable(expression->get_variable()->get_name());
					return 0;
				}
				else
				{
					return found_s->get_value(1.0);
				}
			}
			else
			{
				Error_handler::uninitialised_variable(expression->get_variable()->get_name());
				return 0;
			}
				
		}
	}
	else
	{
		switch (op->get_operator_type())
		{
		case (Token_type::AND) :
			return calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression) && calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression);
			
		case (Token_type::OR) :
			return calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression) || calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression);
			
		case (Token_type::DIVIDE) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) / calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
			
		case (Token_type::MULTIPLY) :
			return calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression) * calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression);
				
		case (Token_type::PLUS) :
			return calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression) + calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression);
			
		case (Token_type::MINUS) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) - calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
			
		case (Token_type::EQUALITY) :
			return calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression) == calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression);
		case (Token_type::INEQUALITY) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) != calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
		case (Token_type::LESS) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) < calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
		case (Token_type::LESS_OR_EQUAL) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) <= calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
		case (Token_type::GREATER) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) > calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
		case (Token_type::GREATER_OR_EQUAL) :
			return calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression) >= calculate_expression(eb, expression->get_right(), false, is_condition, outer_expression);
		case (Token_type::NEGATION) :
			return !(calculate_expression(eb, expression->get_left(), true, is_condition, outer_expression));
			break;
		default: //error
			break;

		}
	}
	
	return 1.0;
}

void Test_generator::change_symbol_in_table(std::shared_ptr<Symbol> old_symbol, std::shared_ptr<Symbol> new_symbol, std::shared_ptr<Executing_block> eb)
{
	for (int i = 0; i < eb->symbol_table.size(); ++i)
	{
		if (eb->symbol_table[i].get() == old_symbol.get())
		{
			eb->symbol_table[i] = new_symbol;
			return;
		}
	}
}


std::shared_ptr<Scanf_parameter> Test_generator::in_scanfs(std::shared_ptr<Executing_block> eb, std::string name)
{
	for (auto& s : eb->scanfs)
	{
		if (s->get_parameter(name) != nullptr)
			return s->get_parameter(name);
	}
	return nullptr;
}

std::shared_ptr<Executing_block> Test_generator::find_executing_block(std::shared_ptr<Block> scope)
{
	for (auto& e : executing_blocks)
	{
		if (e->scope == scope)
			return e;
	}
	return nullptr;
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

std::shared_ptr<Symbol> Test_generator::find_in_symbol_table(std::shared_ptr<Executing_block> eb, std::string name)
{
	for (auto& s : eb->symbol_table)
	{
		if (s->get_name() == name)
			return s;
	}
	return nullptr;
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




