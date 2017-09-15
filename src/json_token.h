/*
Copyright © Nico Zink
All rights reserved.
*/

enum class JSON_Token
{
	begin_object,
	end_object,
	begin_array,
	end_array,
	literal_null,
	literal_true,
	literal_false,
	separator_colon,
	separator_comma,
	string,
	number,
	end_of_input,
};