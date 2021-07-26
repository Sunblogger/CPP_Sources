//****************************************************************************************************************************
// This class logs data to a logfile.
// Version: 0.6
// Date: 08.07.2021
// Made by Fuseless Projects.
//****************************************************************************************************************************

#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <logfile.hpp>	// our include-file for this class

//****************************************************************************************************************************
// we add one message to the logfile with parameters
// logtype: the type of log (info ... error)
// message: the message without date, time we will add to the logfile
//****************************************************************************************************************************
enum logfile_class::returncode logfile_class::addmessage(enum logentrytype const logtype, const std::string message) {
std::chrono::time_point<std::chrono::system_clock> systemtime;	// the current point of time
std::time_t timepoint;
std::string stringtimepoint;
std::string timestamp;

	if (logging_flag == true) { // we log only if logging is enabled 
		#ifdef thread_safe_logging
		std::lock_guard<std::mutex> logfile_lock_guard(logfile_mutex);	// we lock 
		#endif // thread_safe_logging
		logfile.open(logfilename, std::ios_base::app /* | std::ios_base::in | std::ios_base::out | std::ios_base::binary*/);	// we open logfile and want to append data
		if (logfile.is_open() == true) { // file is open, we can write data into it
			systemtime = std::chrono::system_clock::now();
			timepoint = std::chrono::system_clock::to_time_t(systemtime);	// convert current systemtime to a value that represents date + time
			timestamp.resize(23);	// we set the buffer to 23 chars
			std::strftime(&timestamp[0], timestamp.size() + 1, "%d.%m.%Y %X h: ", std::localtime(&timepoint));	// we get the timestamp in format dd.mm.yyyy hh:minmin:secsec
			// now we add a specific string to mark the entry of the logfile either as info, warning or error:
			switch (logtype) {
				case logentrytype::info : logfile << timestamp << "Info: " << message << std::endl;	break;	// now we add the line to the logfile
				case logentrytype::warning : {std::cout << timestamp << "Warning: " << message << '\r' << std::endl; logfile << timestamp << "Warning: " << message << std::endl;} break;		// now we add the line to the logfile
				case logentrytype::error : {std::cout << timestamp << "Error: " << message << '\r' << std::endl; logfile << timestamp << "Error: " << message << std::endl;} break;		// now we add the line to the logfile
			}	// end of switch
			currentsize = logfile.tellp();	// we get size of logfile		
			#ifdef devstage
			std::cout << "Current size: " << currentsize << " Bytes." << "Maximum size: " << maximumsize*1024 << std::endl;
			#endif 
			#ifdef devstage
			std::cout << "Writecounter: " << writecounter << std::endl;
			#endif 
			
			// now we check if we have reached the maximum size of the logfile. But we do this only every 1000 writes to the logfile
			if ( ((writecounter == 0) && (currentsize > maximumsize * 1024)) || ((writecounter > writecounterlimit) && (currentsize > maximumsize * 1024))) truncate_logfile(&timestamp[0]);	// we check if logfile has become greater than limit when we add a message for first time
				else {
				writecounter++;	// we increment counter for writes
				logfile.close();	// we have to close the file
			}
			
			return returncode::NO_ERROR;
		} else {	// file is not open for writing
			logfile.close();	// we have to close the file
			std::cout << "Error: Logfile " << logfilename << " can not be opened for writing!" <<std::endl;
			return returncode::LOGFILE_OPEN_ERROR;
		}	// end of file is not open for writing
		
		return returncode::NO_ERROR;
	} else { // we have nothing to do because logging_flag is false
		return returncode::NO_ERROR;
	}
}	// end of logfile_class::addmessage

//****************************************************************************************************************************************
// truncates the current logfile if its size has reached the limit
//****************************************************************************************************************************************
void logfile_class::truncate_logfile(const char *tstamp) {
unsigned int linecounter = 0, tempcounter;

std::string line_logfile;	

	logfile << tstamp << "Info: Logfile was truncated due to limit of size.";	// we add an info in logfile
	logfile.seekg(0, std::ios_base::beg);	// we get back to start of file
	//std::getline(logfile, line_logfile);
	//++linecounter;
	#ifdef devstage
	std::cout << "We start to count lines of current logfile..." << std::endl;
	#endif // #ifdef devstage
	while (std::getline(logfile, line_logfile)) {	// we count number of lines in logfile
		++linecounter;
	} // end of while
	#ifdef devstage
	std::cout << "We have " << linecounter << " lines found in current logfile" << std::endl;
	#endif // #ifdef devstage
	
	logfile.clear();	// we clear all flags
	logfile.seekg(0 /*, std::ios_base::beg*/);	// we get back to start of file again because now we have to read content and write it to temp. logfile
	linecounter = linecounter / 2;	// we need only the half the lines
	#ifdef devstage
	std::cout << "We start to step through the first half of current logfile..." << std::endl;
	#endif // #ifdef devstage
	for (tempcounter = 0; tempcounter < linecounter; tempcounter++) std::getline(logfile, line_logfile); 	// we step to the half of the file: oldest entries will be ignored
	#ifdef devstage
	std::cout << "We open temporary logfile." << std::endl;
	#endif // #ifdef devstage
	templogfile.open(logfilename + ".tmp", std::ios_base::app);
	if (templogfile.is_open() == true) {
		#ifdef devstage
		std::cout << "We get second half of current logfile and write all lines to temporary logfile..." << std::endl;
		#endif // #ifdef devstage
		while (logfile.good()) {std::getline(logfile, line_logfile); templogfile << line_logfile << std::endl; } 	// now we read the rest of the original logfile and write each line to temp. file
		#ifdef devstage
		std::cout << "We close temporary logfile..." << std::endl;
		#endif // #ifdef devstage
		templogfile.close();	// we close our temporary logfile
		#ifdef devstage
		std::cout << "We close temporary logfile..." << std::endl;
		#endif // #ifdef devstage
		logfile.close();	// we close our logfile	
		std::filesystem::remove(logfilename); 	// we delete the orignal logfile
		std::filesystem::rename(logfilename + ".tmp", logfilename);	// we rename our temporary logfile to our logfile
	} else {	// we could not open temporary logfile for truncating
		logfile.seekp(std::ios_base::end);	// we jump to end of logfile
		logfile << tstamp << "Error: we can not create temporary logfile for truncating the original logfile!" << std::endl;
		std::cout << "Error: we can not create temporary logfile for truncating the original logfile!" << std::endl;
	}
	writecounter = 0;	// we reset the writecounter: 	
}	// end of logfile_class::truncate_logfile

