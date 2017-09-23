/*
Copyright © Nico Zink
All rights reserved.
*/

enum class OSL_Token
{
	closure,
	output,
	color,
	paren_open,
	paren_close,
	brace_open,
	brace_close,
	comma,
	semicolon,
	equals,
	identifier,
	number,
	end_of_input
};