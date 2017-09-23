/*
Copyright © Nico Zink
All rights reserved.
*/

#include "osl_shader.h"

// Local Includes
#include "osl_parser.h"

// Project Includes

// External Includes
#include <fstream>
#include <istream>
#include <sstream>

OSL_Shader::OSL_Shader()
{

}

OSL_Shader OSL_Shader::Parse(std::istream& input)
{
	OSL_Shader result;

	OSL_Parser parser(input);
	parser.Parse(result);

	return result;
}

OSL_Shader OSL_Shader::Parse(const std::string str)
{
	std::istringstream stream(str);
	return Parse(stream);
}

OSL_Shader OSL_Shader::ParseFile(const std::string path)
{
	std::ifstream file(path.c_str());

	return Parse(file);
}
