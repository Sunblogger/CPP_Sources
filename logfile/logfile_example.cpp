/* 	logfile_example.cpp
	Version: 0.2 
	Date: 05.04.2021
	
	This program demonstrates how the logfile-class works (without threads).
	Compile and link: g++ -I<path to logfile.hpp> logfile.o logfile_example.cpp -o logfile_example -lstdc++fs
	
 * Copyright 2020 
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

// #define devstage 	// we are in development stage and print some messages on screen

#include <iostream>
#include <chrono>
#include <logfile.hpp>	// include-file for logfile-class

class myclass {	//this class is an example how to use the logfile-class for logging in your own class:
public:
myclass(logfile_class *log_file) : myclasslogfile(log_file) {std::cout << "This is constructor of myclass." << std::endl;}	// constructor with argument address of logfile

//void log_to_logfile(const logfile_class::logentrytype log_level, const std::string message_to_log) { myclasslogfile->addmessage(log_level, message_to_log);}
logfile_class::returncode  log_to_logfile(const logfile_class::logentrytype log_level, const std::string message_to_log) {
		return myclasslogfile->addmessage(log_level, message_to_log);
	}

private:
logfile_class *myclasslogfile;	// we save a pointer to an object of a logfile-class
};	// end of myclass

int main()
{
std::cout << "logfile example, version 0.1"	<< std::endl;
logfile_class logfile_1("logfile_example_1.log", 10, true);		// we create one object of our class: Name of the logfile: logfile_example.log; maximum-size of logfile: 10 kBytes, logging is enabled = true

// This is an example how to use the logfile-class "native":
logfile_1.addmessage(logfile_class::logentrytype::info, "This is an information.");	// we add one line as information
logfile_1.addmessage(logfile_class::logentrytype::warning, "This is a warning.");	// we add one line as information
logfile_1.addmessage(logfile_class::logentrytype::error, "This is an error.");	// we add one line as information

// This is an example how to use the logfile-class with your own classes:
myclass myobject(&logfile_1); // we create an object of our class and we give as parameter the address of our logfile-object
myobject.log_to_logfile(logfile_class::logfile_class::logentrytype::info, "This is an information from myobject");	// we ignore return-code from logfile-class
myobject.log_to_logfile(logfile_class::logfile_class::logentrytype::warning, "This is a warning from myobject");	// we ignore return-code from logfile-class
myobject.log_to_logfile(logfile_class::logfile_class::logentrytype::error, "This is an error from myobject");		// we ignore return-code from logfile-class

// This is an example how to use the logfile-class with taking care of the return-codes is delivers:
if (myobject.log_to_logfile(logfile_class::logfile_class::logentrytype::error, "This is an error from myobject") != logfile_class::returncode::NO_ERROR)
	std::cout << "Adding message to logfile failed!" << std::endl;

// This is an example how truncating works: We have initialized our object with maximum size of 10 kBytes for the logfile. Now we will put lines to our logfile so that
// we will jump over this size and the logfile class will truncate the file itself to half of 10 kBytes. 
for (unsigned int counter = 0; counter < 20; ++counter) logfile_1.addmessage(logfile_class::logentrytype::info, "This is dummy-line to fill the logfile for testing purposes.");	// we add one line as information for 20 times

// now we use a second object for performance measures with a size of the logfile = 1 MByte:
logfile_class logfile_2("logfile_example_2.log", 1024, true);		// we create one object of our class: Name of the logfile: logfile_example.log; maximum-size of logfile: 10 kBytes, logging is enabled = true
std::chrono::time_point<std::chrono::system_clock> time_start, time_stop;	// the current point of time
time_start = std::chrono::system_clock::now();	// we get the time before we add dummy lines for performance
// now we try to find out how many lines per second can be written to logfile:
for (unsigned int counter = 0; counter < 100*1000; ++counter) logfile_2.addmessage(logfile_class::logentrytype::info, "This is performance test and we add a dummy-line to fill the logfile for testing purposes.");	// we add one line as information for 20 times
time_stop = std::chrono::system_clock::now();	// we get the time after adding the lines to the logfile
std::chrono::system_clock::duration time_to_run = time_stop - time_start;
//unsigned int run_time_milli_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(time_to_run).count();
std::cout << "Time for adding 100.000 lines: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_to_run).count() << " milli-seconds" << std::endl;

std::cout << "Program finished"	<< std::endl;
return 0;
}

