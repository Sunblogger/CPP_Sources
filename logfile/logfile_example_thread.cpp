/* 	logfile_example_thread.cpp
	Version: 0.1 
	Date: 05.04.2021

	This program will use logfile-class in several threads.
	compiling and linking: g++ -lpthread logfile_example_thread.cpp -o lft 
	
	This program was only tested on Raspberry OS on x86- and ARMHF-CPU (the native Raspberry Pi).
		
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

#include <iostream>
#include <mutex>
#include <thread>
#include <logfile.hpp>	// include-file for logfile-class

logfile_class logfile("logfile_example_thread.log", 10, true);		// we create one object of our class: Name of the logfile: logfile_example_thread.log; maximum-size of logfile: 10 kBytes, logging is enabled = true

std::mutex handling_mutex;
// this function will be called by thread:
void parallel_working(const unsigned int counter) {
	std::string line_logfile = "This line was added with threaded logging by thread # ";
	line_logfile.append(std::to_string(counter));
	logfile.addmessage(logfile_class::logentrytype::info, line_logfile);
} 

int main() {

int threadcounter;
const int maximum_threads = 30;
std::thread thread_array[maximum_threads];
for (threadcounter = 0; threadcounter < maximum_threads; threadcounter++) {	// we start threads which will only add a line to the logfile
	try {
		thread_array[threadcounter] = std::thread(parallel_working, threadcounter);	// we start next thread
	} catch (...) { // we catch any exception so that program does not crash
		std::cout << "Exception happened." << std::endl;
	} // end of catch
}
// now we join all threads
for (threadcounter = 0; threadcounter < maximum_threads; threadcounter++) {	
		thread_array[threadcounter].join();
}

std::cout << "Program finished. Check file 'logfile_example_thread.log' for content." << std::endl;

return 0;
}	// end of main
