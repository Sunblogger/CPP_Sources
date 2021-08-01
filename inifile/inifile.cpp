/*
 ini_file_class.cpp
 Release: 0.2, date: 13.04.2021
 
 
 
 
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
 
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <memory>
#include <algorithm>
#include <vector>
#include <inifile.hpp>	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This methods reads the ini-file and puts all variables + content into a map of <string + string> for more easy use
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int ini_file_class::read_ini_file() {
std::ifstream ini_file;		// the filestream we will read all data from
std::string ini_file_line;
std::size_t position;
std::string variable_name, variable_content;

	ini_file.open(ini_file_name);	
	if (ini_file.is_open() == true) {	// we can read file
		while (ini_file.eof() == false) {
			getline(ini_file, ini_file_line);
			position = ini_file_line.find('#');
			if ((position != 0) && (ini_file_line.length() > 0) ) {	// we do not have a comment-marker in first column of the line and line is not empty
				// now we separate the name of the variable from the content	
				position = ini_file_line.find('=');
				if ((position > 0) && (position != std::string::npos)){
					variable_name = ini_file_line.substr(0, position);
					variable_content = ini_file_line.substr(position + 1, ini_file_line.length());
					ini_file_content.insert(make_pair(variable_name, variable_content));	// we fill our map with name of variable and the content in ini-file
				}
			}
		};
		ini_file.close();
	} else {	// file is not open for reading
		std::cout << "Error reading ini-file " << ini_file_name << "." << std::endl;
		return 1;	
	}
	
return 0;
}	// end of ini_file_class::read_ini_file

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This method fills the variables of our program with the values we find in our ini-file. 
// If we find an invalid-value, we stop filling and print a message for the user. 
// Invalid values are: negative value for unsigned int, chars for int, neither "true" nor "false" for bool.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int ini_file_class::fill_variables() {
std::string variable_to_search_for, variable_content;	
std::unique_ptr<variable_struct> temp_var;
std::string::size_type char_counter;
std::size_t	position;	// the position in the string to be converted to an integer or unsigned integer
bool leave_for_loop_flag = false;

for (var_map_iterator = var_map.begin(); var_map_iterator != var_map.end(); ++var_map_iterator) {
	variable_to_search_for = var_map_iterator->first;	// we get variable to search for in map
	if (ini_file_content.find(variable_to_search_for) != ini_file_content.end()) 
		variable_content = ini_file_content.find(variable_to_search_for)->second;
	else variable_content.clear(); 	// we reset the string
	temp_var = std::move(var_map_iterator->second); 	// we can not copy the smart pointer but we have to move it. This move makes the reading of the code more easy
	if (variable_content.length() > 0) {	// we have found content for the variable
		switch (temp_var->var_type) {
			case variable_type::is_string: temp_var->var_string = variable_content; break;
			case variable_type::is_unsigned_int: try {
														temp_var->var_uint = std::stoi(variable_content, &position, 10);	// we convert the string to an unsigned integer
														if (position != variable_content.length()) {
															std::cout << "Error in ini-file: value " << variable_content << " does contain invalid charackters in parameter " << variable_to_search_for << std::endl;
															leave_for_loop_flag = true;
														}
													} catch (const std::invalid_argument &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is not allowed for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_int= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													catch (const std::out_of_range &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is too big number for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_int= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													 break;
			case variable_type::is_signed_int: try {
														temp_var->var_int = std::stoi(variable_content, &position, 10);
														if (position != variable_content.length()) {
															std::cout << "Error in ini-file: value " << variable_content << " does contain invalid charackters in parameter " << variable_to_search_for <<std::endl;
															leave_for_loop_flag = true;
														}
													} catch (const std::invalid_argument &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is not allowed for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_int= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													catch (const std::out_of_range &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is too big number for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_int= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													 break;
			case variable_type::is_double: try {
														temp_var->var_double = std::stold(variable_content, &position);
														if (position != variable_content.length()) {
															std::cout << "Error in ini-file: value " << variable_content << " does contain invalid charackters in parameter " << variable_to_search_for <<std::endl;
															leave_for_loop_flag = true;
														}
													} catch (const std::invalid_argument &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is not allowed for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_double= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													catch (const std::out_of_range &acdc) {
														std::cout << "Error in ini-file: value " << variable_content << " is too big number for parameter " << variable_to_search_for <<std::endl;
														temp_var->var_double= 0;
														leave_for_loop_flag = true;
													}	// end of catch
													 break;


			case variable_type::is_bool:{	// we have to uppercase the found content so that we can compare it with "TRUE" or "FALSE"
											for (char_counter = 0; char_counter < variable_content.length(); ++char_counter) variable_content[char_counter] = std::toupper(variable_content[char_counter]);	// we change all chars to upcase for more easy comparision
											if (variable_content == "TRUE") temp_var->var_bool = true; else 
												if (variable_content == "FALSE") temp_var->var_bool = false; else {
													std::cout << "Error in ini-file: value " << variable_content << " is neither 'true' nor 'false' for parameter " << variable_to_search_for <<std::endl;
													leave_for_loop_flag = true;
												}
											break;
										}
		}	// end of switch
	} else {	// we did not find the value in the ini-file. Maybe this is wanted by user
		temp_var->var_string = not_found_in_ini_file;
	}
	var_map_iterator->second = std::move(temp_var);	// we can not copy the smart pointer but we have to move it
	if (leave_for_loop_flag == true) break;	// some invalid value was detected, we stop here with the loop
}	// end of for-loop
	
	if (leave_for_loop_flag == true) return 1; else return 0;	// some invalid value was detected
	
};	// end of ini_file_class::fill_variables()


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This method sets up a buffer which contains the complete configuration of the program. This buffer can be used to print it on the screen.
// You should overwrite this function in your application but as default it might be usefull.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ini_file_class::setup_ini_file_content(std::string *config_buf) {
char char_buf[200] = "";
	config_buf->clear();	// we clear the buffer first
	for (var_map_iterator = var_map.begin(); var_map_iterator != var_map.end(); ++var_map_iterator) {
		sprintf(char_buf, "Parameter: %s has value: %s\n", var_map_iterator->first.c_str(), var_map_iterator->second->var_string.c_str());
		config_buf->append(char_buf);
	} 	// end of for-loop

};	// end of ini_file_class::setup_ini_file_content


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This methods get a value for a parameter. The methods are overloaded, only the second parameter differs. 
// Returncode: true = OK; false = not OK, we do not have this parameter and therefore no value exists for the mentioned parameter.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ini_file_class::get_value(const std::string parameter, std::string *value) {
	if (var_map.find(parameter) != var_map.end()) {
		*value = var_map[parameter]->var_string;
		return true; 
	} else return false;
};

bool ini_file_class::get_value(const std::string parameter, unsigned int *value) {
	if (var_map.find(parameter) != var_map.end()) {
		*value = var_map[parameter]->var_uint;
		return true; 
	} else return false;
};

bool ini_file_class::get_value(const std::string parameter, int *value) {
	if (var_map.find(parameter) != var_map.end()) {
		*value = var_map[parameter]->var_int;
		return true; 
	} else return false;
};

bool ini_file_class::get_value(const std::string parameter, double *value) {
	if (var_map.find(parameter) != var_map.end()) {
		*value = var_map[parameter]->var_double;
		return true; 
	} else return false;
};

bool ini_file_class::get_value(const std::string parameter, bool *value) {
	if (var_map.find(parameter) != var_map.end()) {
		*value = var_map[parameter]->var_bool;
		return true; 
	} else return false;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This methods set a value for a parameter. The methods are overloaded, only the second parameter differs. 
// Returncode: true = OK; false = not OK, we can not change the value
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ini_file_class::set_value(const std::string parameter, std::string *value) {	// set a string-value
	if (var_map.find(parameter) != var_map.end()) {	// if we have the parameter in our map, we can change its value
		var_map[parameter]->var_string.assign(*value);
		return true; 
	} else return false;
};

bool ini_file_class::set_value(const std::string parameter, unsigned int *value) {	// set a string-value
	if (var_map.find(parameter) != var_map.end()) {	// if we have the parameter in our map, we can change its value
		var_map[parameter]->var_uint = *value;
		return true; 
	} else return false;
};

bool ini_file_class::set_value(const std::string parameter, int *value) {	// set a string-value
	if (var_map.find(parameter) != var_map.end()) {	// if we have the parameter in our map, we can change its value
		var_map[parameter]->var_int = *value;
		return true; 
	} else return false;
};

bool ini_file_class::set_value(const std::string parameter, double *value) {	// set a string-value
	if (var_map.find(parameter) != var_map.end()) {	// if we have the parameter in our map, we can change its value
		var_map[parameter]->var_double = *value;
		return true; 
	} else return false;
};


bool ini_file_class::set_value(const std::string parameter, bool *value) {	// set a string-value
	if (var_map.find(parameter) != var_map.end()) {	// if we have the parameter in our map, we can change its value
		var_map[parameter]->var_bool = *value;
		return true; 
	} else return false;
};

