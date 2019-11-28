#pragma once
#include <string>
#include <iostream>


class Exception {
  private:
    std::string message;
  public:
    Exception(std::string message);
    void print();
};

class TimeoutException: public Exception
{
  public:
    TimeoutException(std::string message) : Exception(message) {}
};
