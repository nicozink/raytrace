/*
Copyright © Nico Zink
All rights reserved.
*/

// Local Includes

// Project Includes
#include <json/json.h>

// External Includes

JSON_Value::JSON_Value()
{
	type = JSON_Type::Null;
}

JSON_Value::JSON_Value(std::string string)
{
	type = JSON_Type::String;
	values.string = new std::string(string);
}

JSON_Value::JSON_Value(bool boolean)
{
	type = JSON_Type::Boolean;
	values.boolean = boolean;
}

JSON_Value::JSON_Value(double number)
{
	type = JSON_Type::Number;
	values.number = number;
}

JSON_Value::JSON_Value(int integer)
{
	type = JSON_Type::Number;
	values.number = integer;
}

JSON_Value& JSON_Value::operator=(std::string string)
{
	set(string);

	return *this;
}

JSON_Value&  JSON_Value::operator=(bool boolean)
{
	set(boolean);

	return *this;
}

JSON_Value&  JSON_Value::operator=(double number)
{
	set(number);

	return *this;
}

JSON_Value&  JSON_Value::operator=(int integer)
{
	set(integer);

	return *this;
}

void JSON_Value::clear()
{
	if (type == JSON_Type::Array)
	{
		delete values.array;
	}
	else if (type == JSON_Type::Object)
	{
		delete values.values;
	}
	else if (type == JSON_Type::String)
	{
		delete values.string;
	}

	type = JSON_Type::Null;
}

template<>
bool JSON_Value::contains<std::string>()
{
	return (type == JSON_Type::String);
}

template <>
bool JSON_Value::contains<bool>()
{
	return (type == JSON_Type::Boolean);
}

template <>
bool JSON_Value::contains<double>()
{
	return (type == JSON_Type::Number);
}

template <>
bool JSON_Value::contains<int>()
{
	return (type == JSON_Type::Number);
}

void JSON_Value::empty_array()
{
	clear();

	type = JSON_Type::Array;
	values.array = new std::vector<JSON_Value>();
}

void JSON_Value::empty_object()
{
	clear();

	type = JSON_Type::Object;
	values.values = new std::map<std::string, JSON_Value>();
}

template<>
std::string JSON_Value::get<std::string>()
{
	return *values.string;
}

template <>
bool JSON_Value::get<bool>()
{
	return values.boolean;
}

template <>
double JSON_Value::get<double>()
{
	return values.number;
}

template <>
int JSON_Value::get<int>()
{
	return (int)values.number;
}

void JSON_Value::insert(std::string name, JSON_Value value)
{
	if (type != JSON_Type::Object)
	{
		empty_object();
	}

	(*values.values)[name] = value;
}

bool JSON_Value::is_array()
{
	return type == JSON_Type::Array;
}

bool JSON_Value::is_empty()
{
	return (size() == 0);
}

bool JSON_Value::is_null()
{
	return type == JSON_Type::Null;
}

bool JSON_Value::is_object()
{
	return type == JSON_Type::Object;
}

void JSON_Value::push_back(JSON_Value value)
{
	if (type != JSON_Type::Array)
	{
		empty_array();
	}

	values.array->push_back(value);
}

void JSON_Value::set(std::string string)
{
	clear();

	type = JSON_Type::String;
	values.string = new std::string(string);
}

void JSON_Value::set(bool boolean)
{
	clear();

	type = JSON_Type::Boolean;
	values.boolean = boolean;
}

void JSON_Value::set(double number)
{
	clear();

	type = JSON_Type::Number;
	values.number = number;
}

void JSON_Value::set(int integer)
{
	clear();

	type = JSON_Type::Number;
	values.number = integer;
}

int JSON_Value::size()
{
	if (is_array())
	{
		return values.array->size();
	}
	else if (is_object())
	{
		return values.values->size();
	}
	else if (!is_null())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

JSON_Value& JSON_Value::operator[](int i)
{
	return (*values.array)[i];
}

JSON_Value& JSON_Value::operator[](std::string str)
{
	return (*values.values)[str];
}