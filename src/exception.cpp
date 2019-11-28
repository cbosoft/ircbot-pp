#include <string>
#include <iostream>

#include "exception.hpp"


Exception::Exception(std::string message)
{ 
  this->message = message; 
}


void Exception::print() {
  std::cout << this->message << std::endl;
}
