/*
 * stop_file_class.cpp
 * Release: 0.3, date: 01.08.2021
 * 
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

#define DEVSTAGE	// we are in development-stage and get some more infos on screen

#include <stopfile.hpp>
//****************************************************************************************************************************
// checks if the stop-file for the program exists. If it exists then we delete the stop-file. This clears the flag.
// returncode: see enum class returncode  
//****************************************************************************************************************************
stop_file_class::returncode stop_file_class::check_stop_file() {

if (true == check_content_flag) {	// we have to check the content of the stop-file
	if (true == std::filesystem::exists(stop_file_name)) {	// if we have a stop-file, we try to open it:
		stop_file.open(stop_file_name);
		if (stop_file.is_open() == true) {	// we can open the file, we will read content
			getline(stop_file, command_in_file);
			stop_file.close();
			std::filesystem::remove(stop_file_name);
			#ifdef DEVSTAGE
			std::cout << "Info: Stop-file was deleted." << std::endl;
			#endif
		} else {	// we can not open stop-file for reading
			return returncode::STOP_FILE_READ_ERROR;
		}
		if (command_in_file.compare(command) == 0) {
			#ifdef DEVSTAGE
			std::cout << "Content of stopfile: \"" << command << "\"" << std::endl;
			#endif
			return returncode::NO_ERROR;
		} else {	// content in stopfile is not correct
			#ifdef DEVSTAGE
			std::cout << "Wrong content in stopfile. We need \"" << command << "\"" << std::endl;
			#endif
			return returncode::WRONG_CONTENT;
		}
	} return returncode::NO_STOP_FILE;

} else {	// we do not check content but only if file exists
	if (std::filesystem::exists(stop_file_name) == true) {	// if file exists we delete it
		if (std::filesystem::remove(stop_file_name) == true) { 
			#ifdef DEVSTAGE
			std::cout << "Info: Stop-file was deleted." << std::endl;
			#endif
			return returncode::NO_ERROR;
		} else return returncode::STOP_FILE_DELETE_ERROR;	// we could not delete stop-file
	} else return returncode::NO_STOP_FILE;
}

}	// end of stop_file_class::check_stop_file


//****************************************************************************************************************************
// creates a stop-file for the program
// returncode: see enum class returncode  
//****************************************************************************************************************************
stop_file_class::returncode stop_file_class::create_stop_file() {
std::ofstream stop_file;	

	if (0 != command.length())	{	// if we have a command which should be written into the file
		stop_file.open(stop_file_name, std::ios_base::out | std::ios_base::trunc);
		if (true == stop_file.is_open()) {	// if we can open the stop-file for writing:
			stop_file << command;	// we write the command into the file;
			stop_file.close();
			return returncode::NO_ERROR;
		} else { // we can not open the stop-file for writing:
			stop_file.close();
			return returncode::STOP_FILE_CREATE_ERROR;
		}
	} else {	// we do not have to write a command in the file
		stop_file.open(stop_file_name, std::ios_base::out | std::ios_base::trunc);
		if (true == stop_file.is_open()) {	// if we can open the stop-file for writing:
			stop_file.close();
			return returncode::NO_ERROR;
		} else { // we can not open the stop-file for writing:
			stop_file.close();
			return returncode::STOP_FILE_CREATE_ERROR;
		}
	}
};	// end of stop_file_class::create_stop_file
