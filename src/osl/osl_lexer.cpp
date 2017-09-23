/*
Copyright © Nico Zink
All rights reserved.
*/

#include "osl_lexer.h"

// System includes
#include <sstream>

OSL_Lexer::OSL_Lexer(std::istream& input)
	: input{ input }
{
	skip_char();
}

OSL_Token OSL_Lexer::get_current_token()
{
	return current_token;
}

double OSL_Lexer::get_number()
{
	return stod(current_string);
}

std::string OSL_Lexer::get_string()
{
	return current_string;
}

OSL_Token OSL_Lexer::read_next()
{
	skip_whitespace();

	if (current_char == '{')
	{
		current_token = OSL_Token::brace_open;
		read("{");
	}
	else if (current_char == '}')
	{
		current_token = OSL_Token::brace_close;
		read("}");
	}
	else if (current_char == '(')
	{
		current_token = OSL_Token::paren_open;
		read("(");
	}
	else if (current_char == ')')
	{
		current_token = OSL_Token::paren_close;
		read(")");
	}
	else if (current_char == ',')
	{
		current_token = OSL_Token::comma;
		read(",");
	}
	else if (current_char == ';')
	{
		current_token = OSL_Token::semicolon;
		read(";");
	}
	else if (current_char == '=')
	{
		current_token = OSL_Token::equals;
		read("=");
	}
	else if ((current_char >= '0' && current_char <= '9') ||
		current_char == '-')
	{
			current_token = OSL_Token::number;
			read_number();
	}
	else if ((current_char >= 'a' && current_char <= 'z') ||
		(current_char >= 'A' && current_char <= 'Z') ||
		current_char == '_')
	{
		read_identifier();

		if (current_string == "closure")
		{
			current_token = OSL_Token::closure;
		}
		else if (current_string == "output")
		{
			current_token = OSL_Token::output;
		}
		else if (current_string == "color")
		{
			current_token = OSL_Token::color;
		}
		else
		{
			current_token = OSL_Token::identifier;
		}
	}
	else if (current_char == 0)
	{
		current_token = OSL_Token::end_of_input;
		current_string = "";
	}

	return current_token;
}

void OSL_Lexer::read(std::string str)
{
	for (auto c : str)
	{
		if (current_char == c)
		{
			skip_char();
		}
		else
		{
			throw "Unexpected character in token.";
		}
	}

	current_string = str;
}

void OSL_Lexer::read_number()
{
	std::string result = "";

	while (
		current_char == '0' ||
		current_char == '1' ||
		current_char == '2' ||
		current_char == '3' ||
		current_char == '4' ||
		current_char == '5' ||
		current_char == '6' ||
		current_char == '7' ||
		current_char == '8' ||
		current_char == '9' ||
		current_char == '-' ||
		current_char == '.')
	{
		result += current_char;

		skip_char();
	}

	current_string = result;
}

void OSL_Lexer::read_identifier()
{
	std::string result = "";

	while ((current_char >= 'a' && current_char <= 'z') ||
		(current_char >= 'A' && current_char <= 'Z') ||
		(current_char >= '0' && current_char <= '9') ||
		current_char == '_')
	{
		result += current_char;

		skip_char();
	}

	current_string = result;
}

void OSL_Lexer::skip_char()
{
	current_char = input.get();
	
	if (input.eof())
	{
		current_char = 0;
	}
}

void OSL_Lexer::skip_whitespace()
{
	while (current_char == ' ' || current_char == '\t' || current_char == '\n' || current_char == '\r')
	{
		skip_char();
	}
}
