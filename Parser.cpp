#include "Parser.h"

Token Parser::go_to_next_token(){
	token_index++;
	Token token = get_current_token();
	return token;
}

Token Parser::go_to_previous_token(){
	token_index--;
	Token token = get_current_token();
	return token;
}

Token Parser::get_current_token()
{
	return scanner.get_tokens().at(token_index);
}

bool Parser::is_in_basic_operands(Token_type type)
{
	if (operand_literals.find(type) != operand_literals.end()) return true;
	else return false;
}

bool Parser::is_in_arithmetic_operators(Token_type type)
{
	if (aritmetic_operators.find(type) != aritmetic_operators.end()) return true;
	else return false;
}

bool Parser::is_rel_operator(Token_type type)
{
	if (rel_operators.find(type) != rel_operators.end()) return true;
	else return false;
}

std::shared_ptr<Symbol> Parser::find_in_symbol_table(std::string name)
{
	for (auto& s : symbol_table)
	{
		if (s->get_name() == name)
		{
			return s;
		}
	}
	return nullptr;
}

void Parser::parse_program()
{
	Output_handler::parsing("program", get_current_token().get_value());
	std::shared_ptr<Program> node = std::make_shared<Program>();

	Token token = get_current_token();
	while (token.get_type() != Token_type::EOFILE)
	{		
		if (token.get_type() == Token_type::DEFINE)
		{
			node->add_to_defines(parse_define());
			token = get_current_token();
			continue;
		}
		if (token.get_type() == Token_type::INCLUDE)
		{
			node->add_include(parse_include());
			token = get_current_token();
			continue;
		}
		if (token.get_type() == Token_type::COMMENT)
		{
			token = go_to_previous_token();
			node->add_comment(parse_comment());
			token = go_to_next_token();
			continue;
		}
		if (token.get_type() == Token_type::TYPE_IDENTIFIER)
		{
			go_to_previous_token();
			std::shared_ptr<Var_declaration> declaration = parse_declaration(nullptr);
			//std::cout << "after declaration global" << std::endl;
			if (declaration == nullptr)
			{
				if (get_current_token().get_type() == Token_type::MAIN)
				{
					go_to_previous_token();
					node->add_main(parse_main());
					break; //after main finish parsing program
				}	
				else
					continue;
			}	
			else
			{
				node->add_declaration(declaration);
				token = go_to_next_token();
				continue;
			}
		}
		else // error! 'unexpected token'
		{
			Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
			token = go_to_next_token();
			continue;
		}

	}
	Output_handler::parsing("program finished", get_current_token().get_value());
	tree_root = node;
}

std::shared_ptr<Main_function> Parser::parse_main()
{
	std::shared_ptr<Main_function> node = std::make_shared<Main_function>();
	Token token = go_to_next_token();

	Output_handler::parsing("main function", get_current_token().get_value());

	std::shared_ptr<Block> ifs = nullptr;
	std::shared_ptr<Instruction> instr = nullptr;
	std::shared_ptr<Return_statement> return_stat = nullptr;
	std::shared_ptr<Loop_stop> loop_stop = nullptr;
	if (find_in_symbol_table("main()") == nullptr)
	{
		std::shared_ptr<Integer_symbol> sym = std::make_shared<Integer_symbol>("main()");
		node->copy_symbol_table_from_parent(symbol_table);
		symbol_table.push_back(sym);
		token = go_to_next_token();
			if (token.get_type() == Token_type::BRACE_OPEN)
			{
				while (true)
				{
					token = go_to_next_token();
					if (token.get_type() == Token_type::BREAK || token.get_type() == Token_type::CONTINUE)
					{
						Output_handler::parsing("loop stop", token.get_value());
						loop_stop = std::make_shared<Loop_stop>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::SEMICOLON)
						{
							continue;
						}
						else //expected semicolon
						{
						}
					}
					else if (token.get_type() == Token_type::RETURN)
					{
						Output_handler::parsing("return", token.get_value());
						return_stat = std::make_shared<Return_statement>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::INTEGER_CONSTANT)
						{
							token = go_to_next_token();
							if (token.get_type() == Token_type::SEMICOLON)
							{
								continue;
							}	
							else //expected semicolon
							{
							}
						}
						else //wrong value of return, only integer
						{

						}
					}
					else if (token.get_type() == Token_type::COMMENT)
					{
						token = go_to_previous_token();
						node->add_comment(parse_comment());
						token = get_current_token();
						continue;
					}
					else if (token.get_type() == Token_type::BRACE_CLOSE)
					{
						return node;
					}
					else
						go_to_previous_token();
					if ((instr = parse_instruction(node)) == nullptr)
					{
						if (get_current_token().get_type() == Token_type::MAIN)
						{
							Error_handler::main_redefinition(token.get_line_no());
							continue;
						}
						if ((ifs = parse_if()) == nullptr)
						{

							if ((ifs = parse_while()) == nullptr)
							{ 
								token = go_to_next_token();
								
								//probably delete this error handler from here
								std::cout << "in main" << std::endl;
								Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());	
								if (token.get_type() == Token_type::IDENTIFIER || token.get_type() == Token_type::TYPE_IDENTIFIER || token.get_type() == Token_type::COMMENT)
									token = go_to_previous_token();
							
							}
							else
							{
								node->add_to_blocks(ifs);
							}
						}
						else
						{
							node->add_to_blocks(ifs);
						}
					}
					else
					{
						node->add_to_instructions(instr);
					}

				}

			}
			else
			{
				Error_handler::expected_different_token(token.get_value(), token.get_line_no(), "{");
				go_to_previous_token();
			}
	}
	else
	{
		Error_handler::main_redefinition(token.get_line_no());
		go_to_next_token();
	}

	
	return node;
}

std::shared_ptr<Define> Parser::parse_define()
{
	Output_handler::parsing("define", get_current_token().get_value());
	std::shared_ptr<Define> node = std::make_shared<Define>();
	std::shared_ptr<Symbol> symbol = nullptr;
	
	std::string name;
	Identifier_type type;
	std::shared_ptr<Variable> var = nullptr;

	//previous token was #define
	Token token = go_to_next_token();;

	if (token.get_type() == Token_type::IDENTIFIER)
	{
		name = token.get_value();
		token = go_to_next_token();
		if (token.get_type() == Token_type::CHARACTER_CONSTANT ||
			token.get_type() == Token_type::INTEGER_CONSTANT ||
			token.get_type() == Token_type::REAL_CONSTANT)
		{
			if (token.get_type() == Token_type::CHARACTER_CONSTANT)		
			{
				//string to char
				char *cstr = new char[token.get_value().length() + 1];
				strcpy(cstr, token.get_value().c_str());
				char value = cstr[1];
				type = Identifier_type::CHAR_ID;
				var = std::make_shared<Variable>(name, type, (char)value, true, true);
				symbol = std::make_shared<Character_symbol>(name, type, (char)value, true, true);
				symbol_table.push_back(symbol);
			}
				
			if (token.get_type() == Token_type::INTEGER_CONSTANT)
			{
				//string to int
				int value = std::stoi(token.get_value());
				type = Identifier_type::INT_ID;
				var = std::make_shared<Variable>(name, type, (int)value, true, true);
				symbol = std::make_shared<Integer_symbol>(name, type, (int)value, true, true);
				symbol_table.push_back(symbol);
			}

			if (token.get_type() == Token_type::REAL_CONSTANT)
			{
				//string to double
				double value = atof(token.get_value().c_str());
				if (value >= FLT_MIN && value <= FLT_MAX)
				{
					type = Identifier_type::FLOAT_ID;
					var = std::make_shared<Variable>(name, type, (float)value, true, true);
					symbol = std::make_shared<Float_symbol>(name, type, (float)value, true, true);
					symbol_table.push_back(symbol);
				}
				else
				{
					type = Identifier_type::DOUBLE_ID;
					var = std::make_shared<Variable>(name, type, value, true, true);
					symbol = std::make_shared<Double_symbol>(name, type, (double)value, true, true);
					symbol_table.push_back(symbol);
				}
			}
			else //error 'expected constant'
			{

			}
		}
		
	}
	else //error 'expected identifier'
	{

	}

	node->set_constant(var);
	go_to_next_token();

	return node;
}

std::shared_ptr<Include> Parser::parse_include()
{
	Output_handler::parsing("include", get_current_token().get_value());
	Token token = get_current_token();
	std::shared_ptr<Include> node = std::make_shared<Include>(token);
	go_to_next_token();
	return node;
}

std::shared_ptr<Var_declaration> Parser::parse_declaration(std::shared_ptr<Block> scope)
{
	std::shared_ptr<Var_declaration> node = std::make_shared<Var_declaration>();
	std::shared_ptr<Symbol> symbol = nullptr;
	std::shared_ptr<Variable> var = nullptr;
	std::shared_ptr<Assignement> assignement = nullptr;

	Token token = go_to_next_token();
	Output_handler::parsing("declaration", get_current_token().get_value());
	Identifier_type type;
	std::string name;

	//if (token.get_type() == Token_type::TYPE_IDENTIFIER)
	//{
		if (token.get_value() == "int")
		{
			type = Identifier_type::INT_ID;
			symbol = std::make_shared<Integer_symbol>("", type);
		}
		else if (token.get_value() == "char")
		{
			type = Identifier_type::CHAR_ID;
			symbol = std::make_shared<Character_symbol>("", type);
		}
		else if (token.get_value() == "float")
		{
			type = Identifier_type::FLOAT_ID;
			symbol = std::make_shared<Float_symbol>("", type);
		}
		else if (token.get_value() == "double")
		{
			type = Identifier_type::DOUBLE_ID;
			symbol = std::make_shared<Double_symbol>("", type);
		}
		token = go_to_next_token();
		if (token.get_type() == Token_type::IDENTIFIER)
		{
			//std::cout << "assignement";
			name = token.get_value();
			var = std::make_shared<Variable>(name, type);
			if (find_in_symbol_table(name) == nullptr)
			{
				symbol->set_name(name);
				if (scope != nullptr)
					scope->add_to_symbol_table(symbol); //else this is program
				symbol_table.push_back(symbol);
				token = go_to_next_token();
			}
			else
			{
				Error_handler::variable_redefinition(name, token.get_line_no());
				token = go_to_next_token();
			}
			
			
			if (token.get_type() == Token_type::ASSIGNMENT)
			{
				//go_to_next_token();
				assignement = parse_assignement(var, symbol);
				token = get_current_token();
				if (token.get_type() == Token_type::SEMICOLON)
				{
					node->set_variable(var);
					node->set_assignement(assignement);
					//go_to_next_token();
					return node;
				}
				else
				{
					Error_handler::expected_different_token(token.get_value(), token.get_line_no(), ";");
					node->set_variable(var);
					node->set_assignement(assignement);
					go_to_previous_token();
					//go_to_next_token();
					return node;
				}
				
			}
			else if (token.get_type() == Token_type::SEMICOLON) //only declaration
			{
				node->set_variable(var);
				//go_to_next_token();
				return node;
			}
		}
		else if (type == Identifier_type::INT_ID && token.get_type() == Token_type::MAIN) 
		{

			return nullptr;
		}
		else // error! 'expected type identifier'
		{
			Error_handler::expected_different_token(token.get_value(), token.get_line_no(), "identifier");
			go_to_previous_token();
			return nullptr;
		}
		
	//}	
	
	
	return node;
}

std::shared_ptr<Assignement> Parser::parse_assignement(std::shared_ptr<Variable> variable, std::shared_ptr<Symbol> symbol)
{
	Output_handler::parsing("assignement", get_current_token().get_value());
	std::shared_ptr<Assignement> node = std::make_shared<Assignement>();
	std::shared_ptr<Assigned> assigned = nullptr;// = std::make_shared<Assigned>();
	
	Token token = go_to_next_token();
	
	if (token.get_type() == Token_type::CHARACTER_CONSTANT)
	{
		char *cstr = new char[token.get_value().length() + 1];
		strcpy(cstr, token.get_value().c_str());
		char value = cstr[1];
		assigned = std::make_shared<Variable>("", Identifier_type::CHAR_ID, value, true, true);
		if (symbol->get_type() != Identifier_type::CHAR_ID)
		{
			Error_handler::wrong_type("char", token.get_line_no(), symbol->get_identifier_type_name());
		}
		else
		{
			symbol->set_value(value);
			variable->set_value(value);
		}
		
		token = go_to_next_token();
		if (token.get_type() == Token_type::SEMICOLON)
		{
			node->set_left(variable);
			node->set_right(assigned);
			return node;
		}
		else // error 'unexpected token'  , semicolon expected
		{
			Error_handler::expected_different_token(get_current_token().get_value(), get_current_token().get_line_no(), ";");
			return node;
		}
	}
	else 
	{
		token = go_to_previous_token();
		assigned = parse_expression();

		token = go_to_next_token();
		if (token.get_type() != Token_type::SEMICOLON) //error - unexpected token
		{
			Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
		}
		
	}

	node->set_left(variable);
	node->set_right(assigned);

	return node;
}

std::shared_ptr<Expression> Parser::parse_expression() {
	
	std::shared_ptr<Expression> left = parse_simple_expression();
	Token token = go_to_next_token();

	//Output_handler::parsing("expression", get_current_token().get_value());

	if (is_rel_operator(token.get_type()))
	{
		std::shared_ptr<Operator> op = std::make_shared<Operator>(token.get_type());
		std::shared_ptr<Expression> right = parse_simple_expression();
		return std::make_shared<Expression>(op, left, right);
	}
	else
	{
		go_to_previous_token();
		return left;
	}
}

std::shared_ptr<Expression> Parser::parse_simple_expression() {
	
	std::shared_ptr<Expression> left;
	Token token = go_to_next_token();

	Output_handler::parsing("simple expression", get_current_token().get_value());

	if (token.get_type() == Token_type::MINUS)
	{
		std::shared_ptr<Operator> op = std::make_shared<Operator>(token.get_type());
		left = std::make_shared<Expression>(op, parse_term(), nullptr);
	}
	else
	{
		token = go_to_previous_token();
		left = parse_term();	
	}

	token = go_to_next_token();

	if (token.get_type() == Token_type::PLUS || token.get_type() == Token_type::MINUS || token.get_type() == Token_type::OR)
	{
		std::shared_ptr<Operator> op = std::make_shared<Operator>(token.get_type());
		return std::make_shared<Expression>(op, left, parse_term());
	}
	else
	{
		token = go_to_previous_token();
		return left;
	}

}
std::shared_ptr<Expression> Parser::parse_term() {
	
	std::shared_ptr<Expression> left = parse_factor();
	Token token = go_to_next_token();

	//Output_handler::parsing("term", get_current_token().get_value());

	if (token.get_type() == Token_type::MULTIPLY || token.get_type() == Token_type::DIVIDE || token.get_type() == Token_type::MODULO || token.get_type() == Token_type::AND)
	{
		std::shared_ptr<Operator> op = std::make_shared<Operator>(token.get_type());
		return std::make_shared<Expression>(op, left, parse_factor());
	}
	else
	{
		token = go_to_previous_token();
		return left;
	}
}


std::shared_ptr<Expression> Parser::parse_factor() {
	
	std::shared_ptr<Expression> result;
	std::shared_ptr<Variable> a;
	Identifier_type type;
	Token token = go_to_next_token();

	Output_handler::parsing("factor", get_current_token().get_value());

	if (is_in_basic_operands(token.get_type()))
	{
		if (token.get_type() == Token_type::IDENTIFIER)
		{
			a = std::make_shared<Variable>(token.get_value(), Identifier_type::UNKNOWN);
		}
		else
		{
			if (token.get_type() == Token_type::INTEGER_CONSTANT)
			{
				//string to int
				int value = std::stoi(token.get_value());
				type = Identifier_type::INT_ID;
				a = std::make_shared<Variable>("", type, (int)value, true, false);
			}

			if (token.get_type() == Token_type::REAL_CONSTANT)
			{
				//string to double
				double value = atof(token.get_value().c_str());
				if (value >= FLT_MIN && value <= FLT_MAX)
				{
					type = Identifier_type::FLOAT_ID;
					a = std::make_shared<Variable>("", type, (float)value, true, false);
				}
				else
				{
					type = Identifier_type::DOUBLE_ID;
					a = std::make_shared<Variable>("", type, value, true, false);
				}
			}
		}
		
		result = std::make_shared<Expression>(nullptr, a, nullptr);
	}
	else if (token.get_type() == Token_type::PARENTHESE_OPEN)
	{
		result = parse_expression();
		token = go_to_next_token();
		if (token.get_type() != Token_type::PARENTHESE_CLOSE)
		{
			token = go_to_previous_token();
			//error!! expected ")"
			result = nullptr;
		}
	}
	else if (token.get_type() == Token_type::NEGATION)
	{
		std::shared_ptr<Operator> op = std::make_shared<Operator>(token.get_type());
		return std::make_shared<Expression>(op, parse_factor(), nullptr);
	}
	else
	{
		Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
		token = go_to_previous_token();
		result = nullptr;
	}
	return result;
}

std::shared_ptr<Instruction> Parser::parse_instruction(std::shared_ptr<Block> scope)
{
	std::shared_ptr<Instruction> node = std::make_shared<Instruction>();
	Token token = go_to_next_token();
	Output_handler::parsing("instruction", get_current_token().get_value());

	std::shared_ptr<Expression> expr = nullptr;

	if (token.get_type() == Token_type::TYPE_IDENTIFIER)
	{
		token = go_to_previous_token();
		std::shared_ptr<Var_declaration> d = parse_declaration(scope); //ended with semicolon
		std::cout << get_current_token().get_value() << std::endl;
		if (d == nullptr)
			return nullptr;
		node->set_declaration(d);
		return node;
	}
	else if (token.get_type() == Token_type::SCANF)
	{
		std::shared_ptr<Scanf> s = parse_scanf();
		node->set_scanf(s);
		return node;
	}
	else if (is_in_basic_operands(token.get_type()))
	{
			token = go_to_next_token();
			if (token.get_type() == Token_type::SEMICOLON)
			{
				std::shared_ptr<Variable> v = std::make_shared<Variable>(go_to_previous_token());
				expr = std::make_shared<Expression>(nullptr, v, nullptr);
				node->set_expression(expr);
				return node;
			}
			else if (token.get_type() == Token_type::ASSIGNMENT)
			{
				token = go_to_previous_token();
				if (token.get_type() == Token_type::IDENTIFIER)
				{
					std::shared_ptr<Variable> v = std::make_shared<Variable>(token);
					std::shared_ptr<Symbol> s = find_in_symbol_table(token.get_value());
					token = go_to_next_token();
					std::shared_ptr<Assignement> a = parse_assignement(v, s);
					node->set_assignement(a);
					return node;
				}
				else //error ! wrong left operand of assignement
				{
					Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
				}
			}
			else
			{
				expr = parse_expression();
				token = go_to_next_token();
				if (token.get_type() == Token_type::SEMICOLON)
				{
					node->set_expression(expr);
					return node;
				}
				else //error unexpected token after expression
				{
					Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
					node->set_expression(expr);
					return node;
				}
			}
			
	}
	else if (token.get_type() == Token_type::SEMICOLON)
	{
		return node;
	}
	else 
	{
		go_to_previous_token();
		return nullptr;
	}				

	return node;
}

std::shared_ptr<If_statement> Parser::parse_if() 
{
	std::shared_ptr<If_statement> node = std::make_shared<If_statement>();
	std::shared_ptr<Condition> cond = nullptr;
	std::shared_ptr<Block> ifs = nullptr;
	std::shared_ptr<Instruction> instr = nullptr;
	std::shared_ptr<Return_statement> return_stat = nullptr;
	std::shared_ptr<Loop_stop> loop_stop = nullptr;
	Token token = go_to_next_token();

	Output_handler::parsing("if statement", get_current_token().get_value());

	if (token.get_type() == Token_type::IF)
	{
		cond = parse_expression();
		if (cond == nullptr) //error missing (condition) 
		{

		}
		else
		{
			node->set_condition(cond);
			token = go_to_next_token();
			if (token.get_type() == Token_type::BRACE_OPEN)
			{
				while (true)
				{
					token = go_to_next_token();
					if (token.get_type() == Token_type::BREAK || token.get_type() == Token_type::CONTINUE)
					{
						Output_handler::parsing("loop_stop", token.get_value());
						loop_stop = std::make_shared<Loop_stop>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::SEMICOLON)
						{
							continue;
						}
						else //expected semicolon
						{
						}
					}
					else if (token.get_type() == Token_type::RETURN)
					{
						Output_handler::parsing("return", token.get_value());
						return_stat = std::make_shared<Return_statement>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::INTEGER_CONSTANT)
						{
							token = go_to_next_token();
							if (token.get_type() == Token_type::SEMICOLON)
							{
								continue;
							}
							else //expected semicolon
							{
							}
						}
						else //wrong value of return, only integer
						{

						}
					}
					else if (token.get_type() == Token_type::COMMENT)
					{
						token = go_to_previous_token();
						node->add_comment(parse_comment());
						token = get_current_token();
						continue;
					}
					else if (token.get_type() == Token_type::BRACE_CLOSE)
					{
						return node;
					}
					else
						go_to_previous_token();
					if ((instr = parse_instruction(node)) == nullptr)
					{

						if ((ifs = parse_if()) == nullptr)
						{

							if ((ifs = parse_while()) == nullptr)
							{ //error unexpected token
								token = go_to_next_token();

								//probably delete this error handler from here
								std::cout << "in if" << std::endl;
								Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
								if (token.get_type() == Token_type::IDENTIFIER || token.get_type() == Token_type::TYPE_IDENTIFIER || token.get_type() == Token_type::COMMENT)
									token = go_to_previous_token();

							}
							else
							{
								node->add_to_blocks(ifs);
							}
						}
						else
						{
							node->add_to_blocks(ifs);
						}
					}
					else
					{
						node->add_to_instructions(instr);
					}

				}

			}
			else //error no block {} in if
			{
			}

		}

	}
	else //error expected
	{
		go_to_previous_token();
		return nullptr;
	}

	return node;
}

std::shared_ptr<While_statement> Parser::parse_while() 
{
	std::shared_ptr<While_statement> node = std::make_shared<While_statement>();
	std::shared_ptr<Condition> cond = nullptr;
	std::shared_ptr<Block> ifs = nullptr;
	std::shared_ptr<Instruction> instr = nullptr;
	std::shared_ptr<Return_statement> return_stat = nullptr;
	std::shared_ptr<Loop_stop> loop_stop = nullptr;
	Token token = go_to_next_token();

	Output_handler::parsing("while statement", get_current_token().get_value());
	if (token.get_type() == Token_type::WHILE)
	{
		cond = parse_expression();
		if (cond == nullptr) //error missing (condition) 
		{

		}
		else
		{
			node->set_condition(cond);
			token = go_to_next_token();
			if (token.get_type() == Token_type::BRACE_OPEN)
			{
				while (true)
				{
					token = go_to_next_token();
					if (token.get_type() == Token_type::BREAK || token.get_type() == Token_type::CONTINUE)
					{
						Output_handler::parsing("loop_stop", token.get_value());
						loop_stop = std::make_shared<Loop_stop>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::SEMICOLON)
						{
							continue;
						}
						else //expected semicolon
						{
						}
					}
					else if (token.get_type() == Token_type::RETURN)
					{
						Output_handler::parsing("return", token.get_value());
						return_stat = std::make_shared<Return_statement>(token);
						token = go_to_next_token();
						if (token.get_type() == Token_type::INTEGER_CONSTANT)
						{
							token = go_to_next_token();
							if (token.get_type() == Token_type::SEMICOLON)
							{
								continue;
							}
							else //expected semicolon
							{
							}
						}
						else //wrong value of return, only integer
						{

						}
					}
					else if (token.get_type() == Token_type::COMMENT)
					{
						token = go_to_previous_token();
						node->add_comment(parse_comment());
						token = get_current_token();
						continue;
					}
					else if (token.get_type() == Token_type::BRACE_CLOSE)
					{
						return node;
					}
					else
						go_to_previous_token();
					if ((instr = parse_instruction(node)) == nullptr)
					{
						if ((ifs = parse_if()) == nullptr)
						{

							if ((ifs = parse_while()) == nullptr)
							{ //error unexpected token
								std::cout << "in while" << std::endl;
								token = go_to_next_token();

								//probably delete this error handler from here
							
								Error_handler::unexpected_token(get_current_token().get_value(), get_current_token().get_line_no());
								if (token.get_type() == Token_type::IDENTIFIER || token.get_type() == Token_type::TYPE_IDENTIFIER || token.get_type() == Token_type::COMMENT)
									token = go_to_previous_token();
							}
							else
							{
								node->add_to_blocks(ifs);
							}
						}
						else
						{
							node->add_to_blocks(ifs);
						}
					}
					else
					{
						node->add_to_instructions(instr);
					}

				}

			}
			else //error no block {} in if
			{

			}

		}

	}
	else
	{
		go_to_previous_token();
		return nullptr;
	}

	return node;
}

std::shared_ptr<Scanf> Parser::parse_scanf() 
{
	std::shared_ptr<Scanf> scanf = std::make_shared<Scanf>();
	Token token = go_to_next_token();
	if (token.get_type() == Token_type::PARENTHESE_OPEN)
	{
		token = go_to_next_token();
		while (true)
		{
			if (token.get_type() == Token_type::SCANF_ARGUMENT)
			{
				token = go_to_next_token();
				if (token.get_type() == Token_type::IDENTIFIER)
				{
					std::shared_ptr<Scanf_parameter> p = std::make_shared<Scanf_parameter>(token);
					std::shared_ptr<Symbol> symbol = find_in_symbol_table(token.get_value());
					if (symbol != nullptr)
					{
						scanf->add_to_parameters(p);
						symbol->add_scanf(scanf);
					}
						
					else
					{
						Error_handler::undeclared_variable(token.get_value(), token.get_line_no());
					}
					token = go_to_next_token();
					if (token.get_type() == Token_type::COMMA)
					{
						token = go_to_next_token();
						continue;
					}
					else if (token.get_type() == Token_type::PARENTHESE_CLOSE)
					{
						token = go_to_next_token();
						if (token.get_type() == Token_type::SEMICOLON)
						{
							return scanf;
						}
							
						else
						{
							Error_handler::expected_different_token(token.get_value(), token.get_line_no(), ";");
							return scanf;
						}
					}
					else
					{
						Error_handler::expected_different_token(token.get_value(), token.get_line_no(), ")");
						token = go_to_next_token();
						return scanf;
					}
				}
				else
				{
					Error_handler::expected_different_token(token.get_value(), token.get_line_no(), "identifier");
					token = go_to_next_token();
					continue;
				}

			}
			else
			{
				Error_handler::expected_different_token(token.get_value(), token.get_line_no(), ")");
				token = go_to_next_token();
				return scanf;
			}
		}
	}
	else
	{
		Error_handler::expected_different_token(token.get_value(), token.get_line_no(), "(");
		token = go_to_next_token();
		return nullptr;
	}
}

std::shared_ptr<Comment> Parser::parse_comment()
{
	std::shared_ptr<Comment> comment = std::make_shared<Comment>();
	Token token = go_to_next_token();
	Output_handler::parsing("comment", token.get_value());

	if (token.get_type() == Token_type::COMMENT)
	{
		comment->set_token(token);
		return comment;
	}
	else
	{
		Error_handler::expected_different_token(token.get_value(), token.get_line_no(), "comment");
		token = go_to_previous_token();
		return nullptr;
	}
	
}




