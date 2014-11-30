#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>

void InitLogFile(std::string);
std::ofstream& GetLogFile();

template<typename A>
static void L(A a){
	if(GetLogFile()) GetLogFile() << a << std::endl;
	std::cout << a << std::endl;
}

template<typename A, typename... T>
static void L(A a, T... t){
	if(GetLogFile()) GetLogFile() << a;
	std::cout << a;
	L(t...);
}

#endif