#include "Scanner.h"


Scanner::Scanner(std::string file) 
{ 
	input_stream.open(file); 
		Output_handler::is_file_open(input_stream.is_open());

	if (input_stream.is_open() && do_analysis())
	{
		Output_handler::scanning_successful();
		for (auto &x : tokens)
		{
			std::cout << x.get_line_no() << '\t';
			//std::cout << x.token_pos << std::endl;
			std::cout << x.get_value() << '\t' << '\t';
			std::cout << token_type_names[x.get_type()] << std::endl;
		}
	}
	else
		Output_handler::scanning_successful(false);
	
}

bool Scanner::do_analysis()
{
	char sign;
	char current_sign = ' ';
	std::streampos token_pos = 0;
	int tmp_pos;
	int current_line_no = 1;
	while (input_stream.get(sign))
	{
		std::string token_name;
		//if (isspace(current_sign) || is_end_of_token(current_sign))
		//{
			if (sign == '\n' || sign == '\r') //new line
			{
				current_line_no++;
				current_sign = sign;
				continue;
			}
			if (isspace(sign)) //other whitespace (space, tab, etc.)
			{
				//just skip it, last token already handled, no new token
				current_sign = sign;
				continue;
			}
			if (isalpha(sign)) //keyword or identifier
			{
				got_alpha(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (isdigit(sign)) //number
			{
				got_digit(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '#') //define or include
			{
				got_sharp(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '!' || sign == '=' || sign == '<' || sign == '>') //single or double operator
			{
				got_comparison_sign(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '/') //comment or division
			{
				got_slash_sign(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '&') //and operator or scanf parameter
			{
				got_and_sign(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '|') //or operator
			{
				got_or_sign(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (is_in_basic_characters(sign)) //other single operator
			{
				got_basic_character(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '\"') //string
			{
				got_double_quotation_mark(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			if (sign == '\'') //character constant
			{
				got_quotation_mark(sign, current_sign, token_pos, tmp_pos, current_line_no, token_name);
				continue;
			}
			else //invalid character ('$', '@' etc.)
			{	
				Error_handler::invalid_character(sign, current_line_no);
			}

		//}
	}
	Token token = new_token("", current_line_no, token_pos, Token_type::EOFILE);
	tokens.push_back(token);
	return true;
}

Token Scanner::new_token(std::string t, int l_no, int c_no, Token_type ty = Token_type::UNDEFINED)
{
	return Token(t, l_no, c_no, ty);
}

bool Scanner::is_end_of_token(char ch)
{
	return std::find(end_of_token.begin(), end_of_token.end(), ch) != end_of_token.end();
}

bool Scanner::is_in_basic_characters(char ch)
{
	return basic_characters.count(ch); //0 if not found
}

bool Scanner::is_in_keywords(std::string s)
{
	return keywords.count(s);
}
void Scanner::got_alpha(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	token_name.push_back(sign);
	while (input_stream.get(sign))
	{
		if (isalnum(sign) || sign == '_')
			token_name.push_back(sign);
		else
		{
			input_stream.unget();
			if (is_in_keywords(token_name))
			{
				Token token = new_token(token_name, current_line_no, token_pos, keywords.at(token_name));
				tokens.push_back(token);
			}
			else if (token_name == "main")
			{
				input_stream.get(sign);
				if (sign == '(')
				{
					token_name.push_back(sign);
					input_stream.get(sign);
					if (sign == ')')
					{
						token_name.push_back(sign);
						Token token = new_token(token_name, current_line_no, token_pos, Token_type::MAIN);
						tokens.push_back(token);
						current_sign = ' ';
					}
					else //main without parentheses!!! ()
					{
						input_stream.unget();
						Error_handler::error_in_main(token_name, current_line_no);
					}
				}
				else //main without parentheses!!! ()
				{
					input_stream.unget();
					Error_handler::error_in_main(token_name, current_line_no);
				}

			}
			else
			{
				Token token = new_token(token_name, current_line_no, token_pos, Token_type::IDENTIFIER);
				tokens.push_back(token);
			}
			break;
		}
	}
	current_sign = ' ';
}
void Scanner::got_digit(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	bool real_number = false;
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	token_name.push_back(sign);
	while (input_stream.get(sign))
	{
		if (isdigit(sign))
		{
			token_name.push_back(sign);
			continue;
		}
		else if (sign == '.' && real_number == false)
		{
			token_name.push_back(sign);
			real_number = true;
			continue;
		}
		else if (isspace(sign) || is_end_of_token(sign))//end of number
		{
			input_stream.unget();
			if (real_number == false)
			{
				Token token = new_token(token_name, current_line_no, token_pos, Token_type::INTEGER_CONSTANT);
				tokens.push_back(token);
			}
			else //real number
			{
				Token token = new_token(token_name, current_line_no, token_pos, Token_type::REAL_CONSTANT);
				tokens.push_back(token);
			}
			break;
		}
		else //invalid token!!! 123abc
		{
			token_name.push_back(sign);
			while (input_stream.get(sign))
			{
				if (isspace(sign) || is_end_of_token(sign))
				{
					input_stream.unget();
					break;
				}
				token_name.push_back(sign);
			}
			Error_handler::invalid_character_in_number(token_name, current_line_no);

		}
		break;
	}
	current_sign = ' ';
}
void Scanner::got_sharp(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	token_name.push_back(sign);
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	while (true)
	{
		input_stream.get(sign);
		if (isspace(sign))
		{
			input_stream.unget();
			break;
		}
		else
			token_name.push_back(sign);
	}
	if (token_name == "#define")
	{
		Token token = new_token(token_name, current_line_no, token_pos, Token_type::DEFINE);
		tokens.push_back(token);
	}
	else if (token_name == "#include")
	{
		while (input_stream.get(sign))
		{
			if (isspace(sign))
				continue;
			else
				break;
		}
		token_name.push_back(' ');
		token_name.push_back(sign);
		while (input_stream.get(sign))
		{
			if (sign == '\n' || sign == '\r')
			{
				current_line_no++;
				break;
			}
			token_name.push_back(sign);
		}
		if (token_name == "#include <stdio.h>")
		{
			Token token = new_token(token_name, current_line_no - 1, token_pos, Token_type::INCLUDE);
			tokens.push_back(token);
		}
		else
			Error_handler::invalid_directive(token_name, current_line_no - 1);
	}
	else
		Error_handler::invalid_directive(token_name, current_line_no);

	current_sign = ' ';

}
void Scanner::got_comparison_sign(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	char previous_sign = current_sign;
	current_sign = sign; //'!' || '=' || '<' || '>'
	input_stream.get(sign);
	if (sign == '=')
	{
		tmp_pos = input_stream.tellg();
		tmp_pos = tmp_pos - 2;
		token_pos = tmp_pos;
		token_name.push_back(current_sign);
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, double_operators.at(token_name));
		tokens.push_back(token);
		current_sign = sign; // '='
	}
	else
	{
		input_stream.unget();
		sign = current_sign;
		current_sign = previous_sign;
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, basic_characters.at(sign));
		tokens.push_back(token);
		current_sign = sign;
	}
}
void Scanner::got_and_sign(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	current_sign = sign;
	input_stream.get(sign);
	if (sign == '&')
	{
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(current_sign);
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, double_operators.at(token_name));
		tokens.push_back(token);
		current_sign = sign;
	}
	else
	{
		input_stream.unget();
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(current_sign);
		Token token = new_token(token_name, current_line_no, token_pos, Token_type::SCANF_ARGUMENT);
		tokens.push_back(token);
		current_sign = sign;
	}
}
void Scanner::got_or_sign(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	char previous_sign = current_sign;
	current_sign = sign;
	input_stream.get(sign);
	if (sign == '|')
	{
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(current_sign);
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, double_operators.at(token_name));
		tokens.push_back(token);
		current_sign = sign;
	}
	else
	{
		input_stream.unget();
		current_sign = ' ';
		Error_handler::invalid_character('|', current_line_no);
	}
}
void Scanner::got_slash_sign(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	char previous_sign = current_sign;
	current_sign = sign; //first '/
	input_stream.get(sign);
	if (sign == '/')
	{
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(current_sign);
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, double_operators.at(token_name));
		tokens.push_back(token);
		current_sign = sign; //second '/'
		while (input_stream.get(sign)) //ignore everything after "//"
		{
			if (sign == '\n' || sign == '\r')
			{
				input_stream.unget();
				break;
			}
		}	
	}
	else //divide
	{
		input_stream.unget();
		sign = current_sign;
		current_sign = previous_sign;
		tmp_pos = input_stream.tellg();
		tmp_pos--;
		token_pos = tmp_pos;
		token_name.push_back(sign);
		Token token = new_token(token_name, current_line_no, token_pos, basic_characters.at(sign));
		tokens.push_back(token);
		current_sign = sign;
	}
}
void Scanner::got_quotation_mark(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	char previous_sign = current_sign;
	token_name.push_back(sign); // '\''
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	input_stream.get(sign); //sign inside
	token_name.push_back(sign);
	if (sign == '\'')
	{
		Error_handler::invalid_character_constant(token_name, current_line_no);
		current_sign = ' ';
		return;
	}
	input_stream.get(sign);
	token_name.push_back(sign);
	if (sign == '\'')
	{
		Token token = new_token(token_name, current_line_no, token_pos, Token_type::CHARACTER_CONSTANT);
		tokens.push_back(token);
	}
	else //invalid token!!! more than one character between ' '
	{
		while (input_stream.get(sign))
		{
			if (sign == '\'')
			{
				token_name.push_back(sign);
				Error_handler::invalid_character_constant(token_name, current_line_no);
				break;
			}
			if (sign == '\n' || sign == '\r')
			{
				Error_handler::quotation_not_closed(token_name, current_line_no);
				current_line_no++;
				break;
			}
			token_name.push_back(sign);
		}
		current_sign = ' ';
	}
}
void Scanner::got_double_quotation_mark(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	token_name.push_back(sign);
	while (input_stream.get(sign))
	{
		token_name.push_back(sign);
		if (sign == '\"')
		{
			current_sign = sign;
			Token token = new_token(token_name, current_line_no, token_pos, Token_type::STRING);
			tokens.push_back(token);
			break;
		}
		if (sign == '\n' || sign == '\r')
		{
			token_name.pop_back();
			Error_handler::quotation_not_closed(token_name, current_line_no);
			current_line_no++;
			break;
			//return false;
		}
	}
	current_sign = ' ';
}
void Scanner::got_basic_character(char &sign, char &current_sign, std::streampos &token_pos, int &tmp_pos, int &current_line_no, std::string &token_name)
{
	tmp_pos = input_stream.tellg();
	tmp_pos--;
	token_pos = tmp_pos;
	token_name.push_back(sign);
	Token token = new_token(token_name, current_line_no, token_pos, basic_characters.at(sign));
	tokens.push_back(token);
	current_sign = sign;
}