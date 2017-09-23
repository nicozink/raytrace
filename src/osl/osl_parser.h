/*
Copyright © Nico Zink
All rights reserved.
*/

#pragma once

// Local includes
#include "osl_lexer.h"
#include "osl_shader_type.h"

// Project insludes

// System includes
#include <istream>
#include <string>

class OSL_Shader;

class OSL_Parser
{
public:
	OSL_Parser(std::istream& input);

	void Parse(OSL_Shader& value);

private:

	void read(OSL_Token token);

	void read_shader(OSL_Shader& value);

	void read_shader_body(OSL_Shader& value);

	std::string read_shader_name();

	void read_shader_parameter(OSL_Shader& value);

	void read_shader_parameters(OSL_Shader& value);

	void read_shader_statement(OSL_Shader& value);

	OSL_Shader_Type read_shader_type();

	void read_shader_value();

	OSL_Lexer lexer;
};