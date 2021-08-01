# Makefile for inifile_example
# Date: 01.08.2021
CXXFLAGS = -g -I/home/pi/cpp_sources -Wall -Wextra -std=c++17

inifile_example:	inifile_example.cpp inifile_example.o /home/pi/cpp_sources/inifile.o 
	g++ $(CXXFLAGS) /home/pi/cpp_sources/inifile.o inifile_example.cpp -o inifile_example
	
inifile.o: /home/pi/cpp_sources/inifile.cpp /home/pi/cpp_sources/inifile.hpp
	g++ $(CXXFLAGS) -c /home/pi/cpp_sources/inifile.cpp -o /home/pi/cpp_sources/inifile.o -lstdc++fs
	
