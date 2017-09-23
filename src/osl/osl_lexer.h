/*
Copyright © Nico Zink
All rights reserved.
*/

#pragma once

// Local includes
#include "osl_token.h"

// Project includes

// System Includes
#include <istream>

class OSL_Lexer
{
public:
	OSL_Lexer(std::istream& input);

	OSL_Token get_current_token();

	double get_number();

	std::string get_string();

	OSL_Token read_next();

private:

	void read(std::string str);

	void read_number();

	void read_identifier();

	void skip_char();

	void skip_whitespace();

private:

	int current_char;
	
	OSL_Token current_token;

	std::string current_string;
	
	std::istream& input;
};