/*
Copyright © Nico Zink
All rights reserved.
*/

#include "osl_parser.h"

// Local Includes
#include "osl_shader.h"

OSL_Parser::OSL_Parser(std::istream& input)
	: lexer{ input }
{
	
}

void OSL_Parser::Parse(OSL_Shader& value)
{
	lexer.read_next();

	read_shader(value);
}

void OSL_Parser::read(OSL_Token token)
{
	if (lexer.get_current_token() != token)
	{
		throw "Encountered wrong token.";
	}

	lexer.read_next();
}

void OSL_Parser::read_shader(OSL_Shader& value)
{
	value.shader_type = read_shader_type();

	std::string shader_name = read_shader_name();

	read_shader_parameters(value);

	read(OSL_Token::brace_open);

	read_shader_body(value);

	read(OSL_Token::brace_close);
}

void OSL_Parser::read_shader_body(OSL_Shader& value)
{
	if (lexer.get_current_token() == OSL_Token::paren_close)
	{
		return;
	}

	while (true)
	{
		read_shader_statement(value);

		if (lexer.get_current_token() != OSL_Token::comma)
		{
			break;
		}
		else
		{
			lexer.read_next();
		}
	}
}

std::string OSL_Parser::read_shader_name()
{
	if (lexer.get_current_token() == OSL_Token::identifier)
	{
		std::string name = lexer.get_string();

		lexer.read_next();

		return name;
	}
	else
	{
		throw "Expected shader name.";
	}
}

void OSL_Parser::read_shader_parameter(OSL_Shader& value)
{
	if (lexer.get_current_token() == OSL_Token::output)
	{
		lexer.read_next();
	}

	if (lexer.get_current_token() == OSL_Token::color)
	{
		lexer.read_next();
	}

	std::string parameter_name;
	if (lexer.get_current_token() == OSL_Token::identifier)
	{
		parameter_name = lexer.get_string();
		lexer.read_next();
	}

	read(OSL_Token::equals);

	read_shader_value();

	if (lexer.get_current_token() == OSL_Token::comma)
	{
		lexer.read_next();

		read_shader_parameter(value);
	}
}

void OSL_Parser::read_shader_parameters(OSL_Shader& value)
{
	read(OSL_Token::paren_open);

	if (lexer.get_current_token() == OSL_Token::paren_close)
	{
		lexer.read_next();
		return;
	}

	read_shader_parameter(value);

	if (lexer.get_current_token() != OSL_Token::paren_close)
	{
		throw "Expected parameters end.";
	}

	lexer.read_next();
}

void OSL_Parser::read_shader_statement(OSL_Shader& value)
{
	std::string var1 = lexer.get_string();
	lexer.read_next();

	read(OSL_Token::equals);

	std::string var2 = lexer.get_string();
	lexer.read_next();

	read(OSL_Token::semicolon);
}

OSL_Shader_Type OSL_Parser::read_shader_type()
{
	OSL_Shader_Type shader_type;

	if (lexer.get_current_token() == OSL_Token::identifier)
	{
		if (lexer.get_string() == "surface")
		{
			shader_type = OSL_Shader_Type::Surface;
		}
		else if (lexer.get_string() == "displacement")
		{
			shader_type = OSL_Shader_Type::Displacement;
		}
		else if (lexer.get_string() == "light")
		{
			shader_type = OSL_Shader_Type::Light;
		}
		else if (lexer.get_string() == "volume")
		{
			shader_type = OSL_Shader_Type::Volume;
		}
		else if (lexer.get_string() == "shader")
		{
			shader_type = OSL_Shader_Type::Shader;
		}
		else
		{
			throw "Unknown shader type.";
		}
	}
	else
	{
		throw "Exxpected shader type.";
	}

	lexer.read_next();

	return shader_type;
}

void OSL_Parser::read_shader_value()
{
	if (lexer.get_current_token() == OSL_Token::number)
	{
		double number = lexer.get_number();
		lexer.read_next();
	}
	else if (lexer.get_current_token() == OSL_Token::color)
	{
		lexer.read_next();

		read(OSL_Token::paren_open);

		double r = lexer.get_number();
		lexer.read_next();

		read(OSL_Token::comma);

		double g = lexer.get_number();
		lexer.read_next();

		read(OSL_Token::comma);

		double b = lexer.get_number();
		lexer.read_next();

		read(OSL_Token::paren_close);
	}
}
