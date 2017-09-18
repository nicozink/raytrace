/*
Copyright © Nico Zink
All rights reserved.
*/

// Local Includes
#include "unit_test_exception.h"

// Project Includes
#include <unittest/test.h>

// System Includes
#include <iostream>

/*
 * Constructors
 */

// Creates a new instance of the UnitTestBase class.
// @param testPrefix The prefix of the unit test.
// @param testName The name of the unit test.
UnitTestBase::UnitTestBase(std::string test_prefix, std::string test_name)
{
	this->test_prefix = test_prefix;
	this->test_name = test_name;

	test_result = UnitTestResult::TestNotRun;
}

// Destroys this instance of the UnitTestBase class.
UnitTestBase::~UnitTestBase()
{
	
}

/*
 * Public Methods
 */

// Gets the error message.
// @returns The error message.
std::string UnitTestBase::get_error()
{
	// The caller might not have assigned an error. Instead of
	// printing an empty line, return a default message.
	if (test_error == "")
	{
		return "The unit test failed.";
	}
	else
	{
		return test_error;
	}
}

// Gets the result of the unit test.
// @returns The unit test result.
UnitTestResult UnitTestBase::get_result()
{
	return test_result;
}

// Runs the unit test.
void UnitTestBase::run()
{
	run_unit_test();

	// If the test result is still 'not run', i.e. it
	// hasn't failed in the mean time, then we can change
	// the result to passed.
	if (test_result == UnitTestResult::TestNotRun)
	{
		test_result = UnitTestResult::TestPassed;
	}
}

// Throw an error if the test has failed.
UnitTestBase* UnitTestBase::throw_error()
{
	return this;
}

/*
 * Operators
 */

// Creates an equals operator, which allows adding a
// stream including an error message. This assignment
// counts as the notification that an error has occurred.
// @param stream The stream operator.
void UnitTestBase::operator=(UnitTestError stream)
{
	test_result = UnitTestResult::TestFailed;

	test_error = stream.get_error();

	throw UnitTestException();
}
