/*
 * inifile_example.cpp
 * Date: 01.08.2021
 * 
 * Copyright 2021  
 * 
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#include <iostream>
#include <inifile.hpp>	// ini-file base-class

class example_ini_file_class : public ini_file_class {
	
public:
example_ini_file_class(const std::string file_name) : 	ini_file_class(file_name) {	// we call constructor of base-class
															setup_variable_map(); 		// we setup a map of variables specific for our program
															return_code = read_ini_file(); 	// we try to read the ini-file for our program
															if (0 == return_code) {
																return_code = fill_variables(); // we fill our map with content from our ini-file
																if (0 != return_code) std::cout << "Error: filling variables into var_map failed!" << std::endl;
															} else std::cout << "Error: reading ini file failed!" << std::endl;
														};

void setup_variable_map() {	// sets up the map for all variables we have to search for in ini-file.	
		// we add now 1 entry for the map: 
		// the parameter we search for in ini-file is "first_name". 
		// The type of the variable is a string. It is filled with default value "<EMPTY VARIABLE>".
		var_map["first_name"] = std::unique_ptr<variable_struct>(new variable_struct {variable_type::is_string, empty_variable, 0, 0, 0.0, false});

		// we add now 1 entry for the map: 
		// the parameter we search for in ini-file is "age_in_years". 
		// The type of the variable is an unsigned integer. It is filled with default value 0.
		var_map["age_in_years"] = std::unique_ptr<variable_struct>(new variable_struct {variable_type::is_unsigned_int, empty_variable, 0, 0, 0.0, false});
		
		// we add now 1 entry for the map: 
		// the parameter we search for in ini-file is "male". 
		// The type of the variable is a boolean. It is filled with default value false.
		var_map["male"] = std::unique_ptr<variable_struct>(new variable_struct {variable_type::is_bool, empty_variable, 0, 0, 0.0, false});
		
		// we add now 1 entry for the map: 
		// the parameter we search for in ini-file is "average_discount_percentage". 
		// The type of the variable is a float. It is filled with default value 0.0.
		var_map["average_discount_percentage"] = std::unique_ptr<variable_struct>(new variable_struct {variable_type::is_double, empty_variable, 0, 0, 0.0, false});
		
		// we add now 1 entry for the map: 
		// the parameter we search for in ini-file is "distance_to_airport". 
		// The type of the variable is an integer. It is filled with default value 0. But in ini-file we have an incorrect value (23km, correct: 23) 
		var_map["distance_to_airport"] = std::unique_ptr<variable_struct>(new variable_struct {variable_type::is_unsigned_int, empty_variable, 0, 0, 0.0, false});

	};	// end of setup_variable_map
};	

int main()
{
std::string first_name,		// variable to hold the value which will be read from ini-file
			city;			// vatriable to hold a value from ini-file
unsigned int 	age_in_years, 	// variable to hold the value which will be read from ini-file
				distance_to_airport;	// variable to hold a value from ini-file
bool male;				// variable to hold the value which will be read from ini-file
double average_discount_percentage; // variable to hold the value which will be read from ini-file


example_ini_file_class example_ini_file("inifile_example.ini");	// we create one object with name of ini-file

// now we try to get the values from the map of ini-file:
	if (true == example_ini_file.get_value("first_name", &first_name)) {
		std::cout << "Value for \"first_name\": " << first_name << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"first_name\" in ini-file!" << std::endl;
	}
	
	if (true == example_ini_file.get_value("age_in_years", &age_in_years)) {
		std::cout << "Value for \"age_in_years\": " << age_in_years << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"age_in_years\" in ini-file!" << std::endl;
	}
	
	if (true == example_ini_file.get_value("male", &male)) {
		if (true == male) 
			std::cout << "Value for \"male\": true" << std::endl;
		else 
			std::cout << "Value for \"male\": false" << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"male\" in ini-file!" << std::endl;
	}
	
	if (true == example_ini_file.get_value("average_discount_percentage", &average_discount_percentage)) {
		std::cout << "Value for \"average_discount_percentage\": " << average_discount_percentage << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"average_discount_percentage\" in ini-file!" << std::endl;
	}

// now we try to get the values from the map of ini-file which does not exist in map:	
	if (true == example_ini_file.get_value("city", &city)) {
		std::cout << "Value for \"city\": " << first_name << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"city\" in ini-file!" << std::endl;
	}

// now we try to get the values from the map of ini-file which has not correct value in ini-file:	
	if (true == example_ini_file.get_value("distance_to_airport", &distance_to_airport)) {
		std::cout << "Value for \"distance_to_airport\": " << distance_to_airport << std::endl;
	} else {	// we did not find a value in the map for our parameter
		std::cout << "Error: we did not find \"disctance_to_airport\" in ini-file!" << std::endl;
	}



	
return 0;
}


