/*
Copyright � Nico Zink
All rights reserved.
*/

#include "json_lexer.h"

// System includes
#include <sstream>

JSON_Lexer::JSON_Lexer(std::istream& input)
	: input{ input }
{
	skip_char();
}

JSON_Token JSON_Lexer::get_current_token()
{
	return current_token;
}

double JSON_Lexer::get_number()
{
	return stod(current_string);
}

std::string JSON_Lexer::get_string()
{
	return current_string;
}

JSON_Token JSON_Lexer::read_next()
{
	skip_whitespace();

	switch (current_char)
	{
		case '{':
			current_token = JSON_Token::begin_object;
			read("{");
			break;

		case '}':
			current_token = JSON_Token::end_object;
			read("}");
			break;
			
		case '[':
			current_token = JSON_Token::begin_array;
			read("[");
			break;
		
		case ']':
			current_token = JSON_Token::end_array;
			read("]");
			break;
		
		case 'n':
			current_token = JSON_Token::literal_null;
			read("null");
			break;

		case 't':
			current_token = JSON_Token::literal_true;
			read("true");
			break;
		
		case 'f':
			current_token = JSON_Token::literal_false;
			read("false");
			break;

		case ':':
			current_token = JSON_Token::separator_colon;
			read(":");
			break;

		case ',':
			current_token = JSON_Token::separator_comma;
			read(",");
			break;

		case '"':
			current_token = JSON_Token::string;
			read_string();
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
			current_token = JSON_Token::number;
			read_number();
			break;
		
		case 0:
			current_token = JSON_Token::end_of_input;
			current_string = "";
			break;
	}

	return current_token;
}

void JSON_Lexer::read(std::string str)
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

void JSON_Lexer::read_number()
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
		current_char == '.')
	{
		result += current_char;

		skip_char();
	}

	current_string = result;
}

void JSON_Lexer::read_string()
{
	if (current_char != '\"')
	{
		throw "String token expected.";
	}

	std::string result = "";

	skip_char();

	while (current_char != '\"')
	{
		if (current_char == 0)
		{
			throw "Unexpected end of input.";
		}

		result += current_char;

		skip_char();
	}

	skip_char();

	current_string = result;
}

void JSON_Lexer::skip_char()
{
	current_char = input.get();
	
	if (input.eof())
	{
		current_char = 0;
	}
}

void JSON_Lexer::skip_whitespace()
{
	while (current_char == ' ' || current_char == '\t' || current_char == '\n' || current_char == '\r')
	{
		skip_char();
	}
}
