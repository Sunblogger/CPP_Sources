//****************************************************************************************************************************
// Include-file for logfile_class
// Version: 0.5
// Date: 02.05.2021
// Made by Fuseless Projects.
//****************************************************************************************************************************


#ifndef _log_file_class_include
#define _log_file_class_include

#include <fstream>

// #define devstage
#define thread_safe_logging	// we define that we want this class threadsafe
#ifdef thread_safe_logging
#include <mutex>
#endif //thread_safe_logging

//#define devstage // we are in development stage and print some messages on screen

//****************************************************************************************************************************
// class for handling logfiles: 
// 3 types of log-entries can be distinguished. 
// When maximum size of logfile expressed in kBytes is reached, the logfile is truncated to half of its size
//****************************************************************************************************************************
class logfile_class {  
public: 
// This enum identifies the different kind of log-entries we can have in our logfile:
enum class logentrytype {	
	info,		// just an information
	warning,	// warning, but not serious
	error		// an error is acoured, you should not ignore
};

// This enum is used for return-codes in our class:
enum class returncode {
	NO_ERROR,				
	LOGFILE_OPEN_ERROR,		// we can not open logfile for any reasons	
	LOGFILE_TRUNCATE_ERROR	// we can not truncate the logfile
};

// constructor: we can init our log-file-object with a filename, the maxsize and a flag which can turn logging on or off
logfile_class(const std::string filename, const unsigned int maxsize, const bool logflag) : logfilename(filename), maximumsize(maxsize), logging_flag(logflag) {};

// this method is used to add a message to the logfile
enum logfile_class::returncode addmessage(enum logentrytype const logtype, const std::string message);
void enable_logging() {logging_flag = true;}		// we want to enable logging
void disable_logging() {logging_flag = false;}		// we want to disable logging
void set_maximum_size(const unsigned int msize) {maximumsize = msize;}	// we want to change the maximum size of the logfile expressed in kBytes (=1024 Bytes)
void set_logfile_filename(const std::string filename) {logfilename = filename;}	// we change the name of the logfile

private:
bool first_call = true;			// specifies that this class is called first time which indicates that we have to check maximum size of logfile. After this check we clear this flag (=set it to false) 
std::string logfilename;		// name of the file which is used as logfile
unsigned int maximumsize = 1024;	// the maximum size of the logfile expressed in kilo-bytes
bool logging_flag = true;		// by default we do logging. If this flag is cleared then we do not write any entries to logfile
unsigned int currentsize = 0; 	// the current size of the logfile expressed in kilo-bytes
unsigned int writecounter = 0;	// how many times did we write to the logfile?
const unsigned int writecounterlimit = 1000; 	// we only check the size when we had more than this limit of writes.
void truncate_logfile(const char * tstamp);		// method/function to truncate the logfile if it becomes larger than configured
std::fstream logfile;			// the stream to save the logfile
std::ofstream templogfile;		// temporary logfile needed for truncating the logfile when it becomes too large. This file will only be written but not read
#ifdef thread_safe_logging
std::mutex logfile_mutex;		// this mutex will be used for a lock-guard so that only one thread can add a message per time
#endif // thread_safe
}; // end of class logfileclass

#endif  
