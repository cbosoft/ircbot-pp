#pragma once
#include <string>
#include <iostream>
#include <exception>


class Exception : public std::runtime_error {
  public:
    Exception(std::string what) : std::runtime_error(what) {};
};

#define EXCEPTION(N) \
class N: public Exception\
{\
  public:\
    N(std::string message) : Exception(message) {}\
};

EXCEPTION(TimeoutException)
