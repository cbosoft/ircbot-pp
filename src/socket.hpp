#pragma once
#include <iostream>
#include <string>
#include <sstream>


class Socket {
  private:
    int fd;
    int timeout;
  public:
    Socket();
    Socket(int port, std::string address);
    std::string readline();
    void write(std::string val);
    void set_timeout(int timeout);
};
