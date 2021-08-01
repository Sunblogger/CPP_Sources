# Makefile for stopfile_example
# Date: 01.08.2021

CXXFLAGS = -g -I/home/pi/cpp_sources -Wall -Wextra -std=c++17

stopfile_example:	stopfile_example.cpp stopfile_example.o /home/pi/cpp_sources/stopfile.o 
	g++ $(CXXFLAGS) -pthread /home/pi/cpp_sources/stopfile.o stopfile_example.cpp -o stopfile_example -lstdc++fs
	
stopfile.o: /home/pi/cpp_sources/stopfile.cpp /home/pi/cpp_sources/stopfile.hpp
	g++ $(CXXFLAGS) -c /home/pi/cpp_sources/stopfile.cpp -o /home/pi/cpp_sources/stopfile.o -lstdc++fs
	
