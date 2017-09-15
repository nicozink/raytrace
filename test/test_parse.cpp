/*
Copyright © Nico Zink
All rights reserved.
*/

// Local Includes

// Project Includes
#include <json/json.h>
#include <unittest/test.h>

// External Includes

TEST(Parse, TestParseEmpty)
{
	auto json = JSON::Parse("");

	ASSERT(json.is_null());
}

TEST(Parse, TestParseNull)
{
	auto json = JSON::Parse(" null ");

	ASSERT(json.is_null());
}

TEST(Parse, TestBooleanTrue)
{
	auto json = JSON::Parse(" true ");

	ASSERT(json.contains<bool>() && json.get<bool>() == true);
}

TEST(Parse, TestBooleanFalse)
{
	auto json = JSON::Parse(" false ");

	ASSERT(json.contains<bool>() && json.get<bool>() == false);
}

TEST(Parse, TestEmptyString)
{
	auto json = JSON::Parse(" \"\" ");

	ASSERT(json.contains<std::string>() && json.get<std::string>() == "");
}

TEST(Parse, TestString)
{
	auto json = JSON::Parse(" \"string\" ");

	ASSERT(json.contains<std::string>() && json.get<std::string>() == "string");
}

TEST(Parse, TestInteger)
{
	auto json = JSON::Parse(" 2 ");

	ASSERT(json.contains<int>() && json.get<int>() == 2);
}

TEST(Parse, TestDouble)
{
	auto json = JSON::Parse(" 2.5 ");

	ASSERT(json.contains<double>() && json.get<double>() == 2.5);
}

TEST(Parse, TestEmptyArray)
{
	auto json = JSON::Parse(" [ ] ");

	ASSERT(json.is_array() && json.is_empty());
}

TEST(Parse, TestOneElementArray)
{
	auto json = JSON::Parse(" [ 1 ] ");

	ASSERT(json.is_array());
	ASSERT(json.size() == 1);
	ASSERT(json[0].get<int>() == 1);
}

TEST(Parse, TestTwoElementArray)
{
	auto json = JSON::Parse(" [ 1, 2 ] ");

	ASSERT(json.is_array());
	ASSERT(json.size() == 2);
	ASSERT(json[0].get<int>() == 1);
	ASSERT(json[1].get<int>() == 2);
}

TEST(Parse, TestEmptyObject)
{
	auto json = JSON::Parse(" { } ");

	ASSERT(json.is_object() && json.is_empty());
}

TEST(Parse, TestOneElementObject)
{
	auto json = JSON::Parse(" { \"1\": 1 } ");

	ASSERT(json.is_object());
	ASSERT(json.size() == 1);
	ASSERT(json["1"].get<int>() == 1);
}

TEST(Parse, TestTwoElementObject)
{
	auto json = JSON::Parse(" { \"1\": 1, \"2\": 2 } ");

	ASSERT(json.is_object());
	ASSERT(json.size() == 2);
	ASSERT(json["1"].get<int>() == 1);
	ASSERT(json["2"].get<int>() == 2);
}