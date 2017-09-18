/*
Copyright © Nico Zink
All rights reserved.
*/

// Local Includes

// Project Includes
#include <unittest/test.h>

// System Includes

/*
 * Constructors
 */

// Creates a new instance of the UnitTestError class.
// @param comments The comments.
// @param isCritical A flag indicating whether this
// error is critical.
UnitTestError::UnitTestError(std::string comments, bool is_critical)
{
  
}

/*
 * Public Methods
 */

// Gets the error message.
// @returns The error message.
std::string UnitTestError::get_error()
{
  return string_stream.str();
}

