#pragma once
#include <sstream>

#include "socket.hpp"

class Robot {
  private:
    Socket socket;
    std::string nickname;
    std::string channel;

  public:
    Robot(std::string nickname, std::string channel);
    void connect(int port, std::string address);
    void run();
};
