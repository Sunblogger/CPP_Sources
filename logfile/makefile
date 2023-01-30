# Makefile for logfile_example and logfile_example_threads
# Date: 30.01.2023
CXXFLAGS = -I/home/pi/cpp_sources/logfile -Wall -Wextra -std=c++2a

all: logfile_example logfile_example_thread logfile.o logfile_thread.o logfile_example_thread.o

logfile_example: logfile_example.o logfile.o logfile.cpp logfile.hpp logfile_example.cpp
	g++ $(CXXFLAGS) logfile.o logfile_example.cpp -o logfile_example -lstdc++fs

logfile_example_thread: logfile_example_thread.o logfile_thread.o logfile_example_thread.cpp
	g++ $(CXXFLAGS) logfile_thread.o logfile_example_thread.cpp -o logfile_example_thread -lstdc++fs -lpthread

logfile.o: logfile.cpp logfile.hpp
	g++ $(CXXFLAGS) -c logfile.cpp -o logfile.o

logfile_thread.o: logfile.cpp logfile.hpp
	g++ $(CXXFLAGS) -c logfile.cpp -o logfile_thread.o

logfile_example_thread.o: logfile_example_thread.cpp
	g++ $(CXXFLAGS) -c logfile_example_thread.cpp -o logfile_example_thread.o
