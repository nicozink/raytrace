/*
Copyright © Nico Zink
All rights reserved.
*/

// Local Includes
#include "json_parser.h"

// Project Includes
#include <json/json.h>

// External Includes
#include <istream>
#include <sstream>

JSON::JSON()
{

}

JSON JSON::Parse(std::istream& input)
{
	JSON result;

	JSON_Parser parser(input); 
	parser.Parse(result);

	return result;
}

JSON JSON::Parse(const std::string str)
{
	return Parse(std::istringstream(str));
}
