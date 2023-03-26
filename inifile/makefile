# Makefile for inifile_example
# Date: 26.03.2023
CXXFLAGS = -g -I$(HOME)/cpp_sources/inifile -Wall -Wextra -std=c++17

inifile_example: inifile_example.cpp inifile_example.o inifile.o 
	g++ $(CXXFLAGS) inifile.o inifile_example.cpp -o inifile_example
	
inifile.o: inifile.cpp inifile.hpp
	g++ $(CXXFLAGS) -c inifile.cpp -o inifile.o -lstdc++fs
	
