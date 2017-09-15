/*
Copyright © Nico Zink
All rights reserved.
*/

#pragma once

#ifndef JSON_H
#define JSON_H

// Local Includes

// Project Includes

// External Includes
#include <map>
#include <string>
#include <vector>

class JSON_Value
{
public:

	JSON_Value();

	JSON_Value(std::string string);

	JSON_Value(bool boolean);

	JSON_Value(double number);

	JSON_Value(int integer);

	JSON_Value& operator=(std::string string);

	JSON_Value& operator=(bool boolean);

	JSON_Value& operator=(double number);

	JSON_Value& operator=(int integer);

	void clear();

	template <typename T>
	bool contains();

	void empty_array();

	void empty_object();

	template <typename T>
	T get();

	void insert(std::string name, JSON_Value value);

	bool is_array();

	bool is_empty();

	bool is_null();

	bool is_object();

	void push_back(JSON_Value value);

	void set(std::string string);

	void set(bool boolean);

	void set(double number);

	void set(int integer);

	int size();

	JSON_Value& operator[](int i);

	JSON_Value& operator[](std::string i);

private:

	enum class JSON_Type
	{
		Null,
		Array,
		Object,
		String,
		Boolean,
		Number
	} type;

	union Contents
	{
		std::map<std::string, JSON_Value>* values;

		std::vector<JSON_Value>* array;

		std::string* string;

		bool boolean;

		double number;
	} values;
};

template <>
std::string JSON_Value::get<std::string>();

template <>
bool JSON_Value::get<bool>();

template <>
double JSON_Value::get<double>();

template <>
int JSON_Value::get<int>();

template <>
bool JSON_Value::contains<std::string>();

template <>
bool JSON_Value::contains<bool>();

template <>
bool JSON_Value::contains<double>();

template <>
bool JSON_Value::contains<int>();

class JSON : public JSON_Value
{
public:

	JSON();

	static JSON Parse(std::istream& input);

	static JSON Parse(const std::string str);

private:

};

#endif
