/*
Copyright � Nico Zink
All rights reserved.
*/

#pragma once

// Local includes
#include "json_lexer.h"

// Project insludes
#include <json/json.h>

// System includes
#include <istream>

class JSON_Parser
{
public:
	JSON_Parser(std::istream& input);

	void Parse(JSON_Value& value);

private:

	void read_json_array(JSON_Value& value);

	void read_json_array_value(JSON_Value& value);

	void read_json_object(JSON_Value& value);

	void read_json_object_value(JSON_Value& value);

	void read_json_value(JSON_Value& value);

	JSON_Lexer lexer;
};