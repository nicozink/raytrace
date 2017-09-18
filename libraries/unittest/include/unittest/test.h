/*
Copyright � Nico Zink
All rights reserved.
*/

#pragma once

#ifndef UNITTEST_H
#define UNITTEST_H

// Local Includes

// Project Includes

// External Includes
#include <stdio.h>
#include <sstream>
#include <string>

//-----------------------------------------------------------------------------
// Macro definitions
//-----------------------------------------------------------------------------

// Defines a macro which throws an error.
#define TEST_FAILED(comment) \
	*throw_error() = UnitTestError(comment, true)

#define TEST_PASSED() \
	(void)0

#define TEST_ERROR \
	TEST_FAILED("An error was thrown.")

#define ASSERT(CONDITION) \
	if (CONDITION) \
	{ \
		TEST_PASSED(); \
	} \
	else \
	TEST_FAILED(#CONDITION) \

#define ASSERT_TRUE(CONDITION) \
	if (CONDITION) \
	{ \
		TEST_PASSED(); \
	} \
	else \
		TEST_FAILED(#CONDITION) \

#define ASSERT_FALSE(CONDITION) \
	if (!(CONDITION)) \
	{ \
		TEST_PASSED(); \
	} \
	else \
	TEST_FAILED(#CONDITION) \

#define ASSERT_EQ(VALUE1, VALUE2) \
	if (VALUE1 == VALUE2) \
	{ \
		TEST_PASSED(); \
	} \
	else \
		TEST_FAILED(#VALUE1 " and " #VALUE2 "do not match.") \

//-----------------------------------------------------------------------------
// Defines a TEST, which declares a unit test.
//-----------------------------------------------------------------------------
#define TEST(TESTPREFIX, TESTNAME) \
	class TestInfo; \
	class TESTPREFIX##TESTNAME : public UnitTestBase \
	{ \
	public: \
		TESTPREFIX##TESTNAME() \
		: UnitTestBase(#TESTPREFIX, #TESTNAME) \
		{ } \
		void run_unit_test() override; \
	private: \
		static TestInfo* test_info; \
	}; \
	TestInfo* TESTPREFIX##TESTNAME::test_info = UnitTests::RegisterTest(#TESTPREFIX, #TESTNAME, new TESTPREFIX##TESTNAME()); \
	void TESTPREFIX##TESTNAME::run_unit_test()

//-----------------------------------------------------------------------------
// Declare an enum type which indicates the result of a unit test.
//-----------------------------------------------------------------------------
enum class UnitTestResult
{
	// The unit test has not been run.
	TestNotRun,

	// The test has passed.
	TestPassed,

	// The test failed.
	TestFailed,
};

//-----------------------------------------------------------------------------
// Stores any error encountered when running a unit test.
//-----------------------------------------------------------------------------
class UnitTestError
{
public:

	// Creates a new instance of the UnitTestError class.
	// @param comments The comments.
	// @param isCritical A flag indicating whether this
	// error is critical.
	UnitTestError(std::string comments, bool is_critical);

	// Gets the error message.
	// @returns The error message.
	std::string get_error();

	// This operator handles streaming of an integer value.
	inline UnitTestError& operator<<(int input)
	{
		string_stream << input;

		return *this;
	}

	// This operator handles streaming of a string value.
	inline UnitTestError& operator<<(std::string input)
	{
		string_stream << input;

		return *this;
	}

private:

	// Stores the stream object which accepts input from the
	// caller.
	std::stringstream string_stream;
};

//-----------------------------------------------------------------------------
// Stores a unit test.
//-----------------------------------------------------------------------------
class UnitTestError;
class TestInfo;
class UnitTestBase
{
public:

	/*
	* Constructors
	*/

	// Creates a new instance of the UnitTestBase class.
	// @param test_prefix The prefix of the unit test.
	// @param test_name The name of the unit test.
	UnitTestBase(std::string test_prefix, std::string test_name);

	// Destroys this instance of the UnitTestBase class.
	virtual ~UnitTestBase();

	/*
	* Public Virtual Methods
	*/

	// Runs the unit test.
	virtual void run_unit_test() = 0;

	/*
	* Public Methods
	*/

	// Gets the error message.
	// @returns The error message.
	std::string get_error();

	// Gets the result of the unit test.
	// @returns The unit test result.
	UnitTestResult get_result();

	// Runs the unit test.
	void run();

	// Returns an instance of itself to which an error can
	// be assigned.
	UnitTestBase* throw_error();

	/*
	* Operators
	*/

	// Creates an equals operator, which allows adding a
	// stream including an error message. This assignment
	// counts as the notification that an error has occurred.
	// @param stream The stream operator.
	void operator=(UnitTestError stream);

private:

	/*
	* Private Variables
	*/

	// Stores the test error.
	std::string test_error;

	// Stores the test name.
	std::string test_name;

	// Stores the test prefix.
	std::string test_prefix;

	/// Stores the test result.
	UnitTestResult test_result;
};

namespace UnitTests
{
	// Register a unit test.
	// @param testCase The test case.
	// @param testName The test name.
	TestInfo* RegisterTest(std::string testCase, std::string testName, UnitTestBase* unitTest);

	// Runs all unit tests.
	bool Run();
};

#endif
