#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>
using namespace std;

class Exceptions{
	string message;
public:
	Exceptions();
	Exceptions(string message);
	string getMsg();
};

#include "Exceptions.cpp"
#endif