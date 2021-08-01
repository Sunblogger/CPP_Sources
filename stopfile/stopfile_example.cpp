/*
 * stopfile_example.cpp
 * Release 0.1, Date: 01.08.2021
 * 
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

#include <iostream>
#include <thread>
#include <stopfile.hpp>	// stop-file base-class

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// program specific class for handling stop-files. This class is derived from general class stop_file_class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class example_stop_file_class : public stop_file_class {

public:	
example_stop_file_class(const std::string file_name, const std::string command_to_search) : stop_file_class(file_name, command_to_search) {};	// we call constructor of base-class with 2 parameters: name of stop-file and command in stop-file
example_stop_file_class(const std::string file_name) : stop_file_class(file_name) {};	// we call constructor of base-class with one parameter: name of stop-file
void thread_check_stop_file();	
};

void example_stop_file_class::thread_check_stop_file() {
	stop_file_class::returncode result;	// the result of checking the stop-file
	while (true)  {	// we repeat this loop until we break it
		result = check_stop_file();
		if ( (stop_file_class::returncode::NO_STOP_FILE == result) || (stop_file_class::returncode::WRONG_CONTENT == result)) // if we do not have a stop-file or if content is not correct we will simply sleep for a while
			std::this_thread::sleep_for(std::chrono::milliseconds(100));	// we sleep for 100 milliseconds 
		else break;	// we have a stop-file and if we have to check the content the file has correct content
	}
};	// end of example_stop_file_class


int main(int argc, char **argv)
{

std::cout << "Number of parameters to program: " << argc << std::endl;
example_stop_file_class example_stop_file((std::string)(argv[0]) + std::string(".stop"));	// we create one object with name of stop-file. We take as name the current-path + name of programm + suffix '.stop'
example_stop_file_class example_stop_file_with_content((std::string)(argv[0]) + std::string(".stop"), "stopme");	// we create one object with name of stop-file. We take as name the current-path + name of programm + suffix '.stop'. The stopfile should contain string "stopme"

std::cout << "Now we search for stop-file " << example_stop_file.get_stopfile_name() << " ..." << std::endl;
std::thread stop_file_thread(&example_stop_file_class::thread_check_stop_file, &example_stop_file);	// we start a thread which is scanning for stop-file

if (true == stop_file_thread.joinable()) { 	// if the thread is joinable:
			stop_file_thread.join();		// we join the thread: we wait until the thread comes to an end
			std::cout << "We joined thread for processing stop-files successfully." << std::endl;
} else std::cout << "We can not join thread for processing stop-files!" << std::endl;

std::cout << "Now we search for stop-file " << example_stop_file.get_stopfile_name() << " and we search for content ..." << std::endl;
std::thread stop_file_thread_with_content(&example_stop_file_class::thread_check_stop_file, &example_stop_file_with_content);	// we start a thread which is scanning for stop-file

if (true == stop_file_thread_with_content.joinable()) { 	// if the thread is joinable:
			stop_file_thread_with_content.join();		// we join the thread
			std::cout << "We joined thread for processing stop-files with content successfully." << std::endl;
} else std::cout << "We can not join thread for processing stop-files with content!" << std::endl;
	
return 0;
}


