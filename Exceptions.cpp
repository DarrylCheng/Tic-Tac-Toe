#include "Exceptions.h"

Exceptions::Exceptions(){
	message = "Error Occured!";
}

Exceptions::Exceptions(string message){
	this->message = message;
}

string Exceptions::getMsg() { return message; }