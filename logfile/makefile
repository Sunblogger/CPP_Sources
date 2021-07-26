# Makefile for logfile_example and logfile_example_threads
# Date: 09.04.2021
CXXFLAGS = -I/home/pi/cpp_sources -Wall -Wextra -std=c++2a

logfile.o: /home/pi/cpp_sources/logfile.cpp /home/pi/cpp_sources/logfile.hpp
	g++ $(CXXFLAGS) -c /home/pi/cpp_sources/logfile.cpp -o logfile.o -lstdc++fs

logfile_example: logfile_example.o logfile.o
	g++ $(CXXFLAGS) logfile.o logfile_example.cpp -o logfile_example -lstdc++fs

logfile_thread.o: /home/pi/cpp_sources/logfile.cpp /home/pi/cpp_sources/logfile.hpp
	g++ $(CXXFLAGS) -c /home/pi/cpp_sources/logfile.cpp -o logfile_thread.o -lstdc++fs -lpthread
	
logfile_example_thread: logfile_example_thread.o logfile_thread.o
	g++ $(CXXFLAGS) logfile_thread.o logfile_example_thread.cpp -o logfile_example_thread -lstdc++fs -lpthread
