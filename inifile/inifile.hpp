#ifndef _ini_file_class_include
#define _ini_file_class_include

/*
 ini_file_class.hpp
 Release: 0.3, date: 29.01.2023
 
 * Copyright 2021
 * 
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#define _DEVSTAGE	// we are in development-stage and get some more infos on screen

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class works with ini-files and is the base-class.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ini_file_class {  
	
public:
const std::string not_found_in_ini_file = "<NOT FOUND IN INIFILE>";	// this is marker that we expect to find a parameter in ini-file but it is not present in ini-file
// constructor with one parameter: the file-name which contains the ini-data
ini_file_class(const std::string file_name) : ini_file_name (file_name) {};	// we initialize the variable ini_file_name with given parameter
												
void print_ini_file_content() { setup_ini_file_content(&temp_string_buffer); std::cout << temp_string_buffer << std::endl; };	// prints the content of the ini-file on screen	 
// these methods will get a value to a parameter:
bool get_value(const std::string parameter, std::string *value);	// get a string as value for a parameter
bool get_value(const std::string parameter, unsigned int *value);	// get an unsigned int as value for a parameter
bool get_value(const std::string parameter, int *value);			// get an int as value for a parameter
bool get_value(const std::string parameter, double *value);			// get a double as value for a parameter
bool get_value(const std::string parameter, bool *value);			// get a bool as value for a parameter

// these methods will set a value to a parameter:
bool set_value(const std::string parameter, std::string *value);	// set a string-value
bool set_value(const std::string parameter, unsigned int *value);	// set a string-value
bool set_value(const std::string parameter, int *value);	// set a string-value
bool set_value(const std::string parameter, double *value);	// set a string-value
bool set_value(const std::string parameter, bool *value);	// set a string-value

std::string get_not_found_marker() {return not_found_in_ini_file;};			// get the string which marks that we did not find a value for our parameter

protected:	// the following values can be used in derived classes but only internally
bool error_status_flag = true;		// flags the error-status of the ini-object: true = we have an error
bool warning_status_flag = true;	// flags the warning-status of the ini-objeect: true = we have a warning
std::string ini_file_name;			// the name of the ini-file we will read from
unsigned int return_code;			// a return-code to handle errors in the constructor

enum class variable_type {	// this types of variable can we have in our ini-file:
	is_string,			// variable is a string		
	is_unsigned_int,	// variable is an unsigned int
	is_signed_int,		// variable is a signed int and can have positive and negative values
	is_double,			// variable is float
	is_bool				// variable is a bool 
};

struct variable_struct {		// this struct holds 1 variable
	variable_type var_type;		// the type of the variable (int, string, bool ...)
	std::string var_string;		// if variable_type is a strning, then we save the string-value here
	int var_int = 0;			// if variable_type is an int, then we save the int-value of the string here
	unsigned int var_uint = 0;	// if variable_type is an unsigned int, then we save the unsigned int-value of the string here
	double var_double = 0;
	bool	var_bool = false;	// if variable_type is a bool, then we save the bool-value of the string here
};	// end of variable_struct

std::map<std::string, std::string> ini_file_content;	// this map will contain all valid lines from ini-file: first of the map is allways the parameter and second is allways the value found in the ini-file (this is also allways a string)
std::map<const std::string, std::unique_ptr<variable_struct>> var_map;	// the map which contains the variables and and a struct which holds the value
std::map<const std::string, std::unique_ptr<variable_struct>>::iterator var_map_iterator;	// an iterator over the map 
const std::string empty_variable = "<EMPTY VARIABLE>";	// this is default for string-values in our map called var_map

bool valid_ini_data_flag = false;	// flags if we have valid ini-data or not default is false
std::string temp_string_buffer;
unsigned int ini_file_paramater_count = 0;	// the # of parameters we have found in ini-file

//void set_filename(const std::string file_name) { ini_file_name = file_name;}
unsigned int read_ini_file();	// reads the inifile
unsigned int fill_variables();	// fills the variables
void setup_ini_file_content(std::string *config_buf);	// This method sets up a buffer which contains the complete configuration of the program

};	// end of ini_file_class

#endif // #define _ini_file_class_include
