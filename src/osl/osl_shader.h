/*
Copyright © Nico Zink
All rights reserved.
*/

#pragma once

// Local Includes
#include "osl_shader_type.h"

// Project Includes

// External Includes
#include <map>
#include <string>
#include <vector>

class OSL_Parser;
class OSL_Shader
{
	friend class OSL_Parser;

public:

	OSL_Shader();

	static OSL_Shader Parse(std::istream& input);

	static OSL_Shader Parse(const std::string str);

	static OSL_Shader ParseFile(const std::string path);

private:

	OSL_Shader_Type shader_type;
};
