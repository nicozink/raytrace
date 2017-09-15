/*
Copyright © Nico Zink
All rights reserved.
*/

#include "json_parser.h"

JSON_Parser::JSON_Parser(std::istream& input)
	: lexer{ input }
{
	
}

void JSON_Parser::Parse(JSON_Value& value)
{
	lexer.read_next();

	if (lexer.get_current_token() != JSON_Token::end_of_input)
	{
		read_json_value(value);
	}
	else
	{
		value.is_null();
	}

	if (lexer.get_current_token() != JSON_Token::end_of_input)
	{
		throw ("Expected end iof input.");
	}
}

void JSON_Parser::read_json_array(JSON_Value& value)
{
	if (lexer.get_current_token() != JSON_Token::begin_array)
	{
		throw "Expected array start.";
	}

	lexer.read_next();

	if (lexer.get_current_token() == JSON_Token::end_array)
	{
		value.empty_array();
		lexer.read_next();

		return;
	}

	read_json_array_value(value);

	if (lexer.get_current_token() != JSON_Token::end_array)
	{
		throw "Expected array end.";
	}

	lexer.read_next();
}

void JSON_Parser::read_json_array_value(JSON_Value& value)
{
	JSON_Value new_value;

	read_json_value(new_value);

	value.push_back(new_value);

	if (lexer.get_current_token() == JSON_Token::separator_comma)
	{
		lexer.read_next();

		read_json_array_value(value);
	}
}

void JSON_Parser::read_json_object(JSON_Value& value)
{
	if (lexer.get_current_token() != JSON_Token::begin_object)
	{
		throw "Expected array object.";
	}

	lexer.read_next();

	if (lexer.get_current_token() == JSON_Token::end_object)
	{
		value.empty_object();
		lexer.read_next();

		return;
	}

	read_json_object_value(value);

	if (lexer.get_current_token() != JSON_Token::end_object)
	{
		throw "Expected object end.";
	}

	lexer.read_next();
}

void JSON_Parser::read_json_object_value(JSON_Value& value)
{
	if (lexer.get_current_token() != JSON_Token::string)
	{
		throw "Expected string token.";
	}

	std::string value_name = lexer.get_string();

	lexer.read_next();

	if (lexer.get_current_token() != JSON_Token::separator_colon)
	{
		throw "Expected colon separator token.";
	}

	lexer.read_next();

	JSON_Value new_value;

	read_json_value(new_value);

	value.insert(value_name, new_value);

	if (lexer.get_current_token() == JSON_Token::separator_comma)
	{
		lexer.read_next();

		read_json_object_value(value);
	}
}

void JSON_Parser::read_json_value(JSON_Value& value)
{
	switch (lexer.get_current_token())
	{
		case JSON_Token::literal_null:
			value.clear();
			lexer.read_next();
			break;
		case JSON_Token::literal_true:
			value.set(true);
			lexer.read_next();
			break;
		case JSON_Token::literal_false:
			value.set(false);
			lexer.read_next();
			break;
		case JSON_Token::begin_array:
			read_json_array(value);
			break;
		case JSON_Token::begin_object:
			read_json_object(value);
			break;
		case JSON_Token::string:
			value.set(lexer.get_string());
			lexer.read_next();
			break;
		case JSON_Token::number:
			value.set(lexer.get_number());
			lexer.read_next();
			break;
		default:
			throw "Expected a json value.";
	}
}