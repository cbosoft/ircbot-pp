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
