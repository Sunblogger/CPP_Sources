#ifndef _stop_file_class_include
#define _stopf_file_class_include
/*
 * stop_file_class.hpp
 * Release: 0.3, date: 01.08.2021
 * Copyright 2021
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <logfile.hpp>
//****************************************************************************************************************************
// Class to handle with files which are used to flag for our program that we want to stop. 
// As an option we can specify a command in the file which is to be evaluated. 
// When we detect the stop-file we deleted to clear this flag.
//****************************************************************************************************************************
class stop_file_class {
public:
	enum class returncode {		// define returncodes for this class
		NO_ERROR,				// no error
		NO_STOP_FILE,			// we do not have a stop-file
		STOP_FILE_DELETE_ERROR,	// an error is acoured
		STOP_FILE_READ_ERROR,	// we can not read the stop-file
		STOP_FILE_CREATE_ERROR,	// we could not create the stop-file
		WRONG_CONTENT			// we have not correct content in stop-file
	};

stop_file_class(const std::string file_name, const std::string command_to_search) : stop_file_name(file_name), command(command_to_search) {check_content_flag = true;}	// constructor with 2 parameters: name of stop-file + content in file we want to search for. If we call this constructor, we change the flag check_content_flag to 'true'
stop_file_class(const std::string file_name) : stop_file_name(file_name) {} 	// constructor with only 1 parameter: name of stop-file
stop_file_class::returncode check_stop_file();	// method that checks if we have a stop-file 
std::string get_stopfile_name() {return stop_file_name;};	// tells us the filename
returncode create_stop_file();	// method to create a stop-file

private:
	std::string command_in_file;		// the command we find in the file
	std::string stop_file_name;			// the name of the file which contains the command stop_program
	std::string command = "";			// the command we expect to see
	bool check_content_flag = false;	// flags if we have to check the content of the stop-file (yes or no)
	std::ifstream stop_file;			// the file which contains the command
};	// end of stop_file_class

#endif	// #ifndef _stop_file_class_include
