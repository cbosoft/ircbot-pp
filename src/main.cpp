#include <iostream>
#include <string>
#include <sstream>

#include "robot.hpp"

int main(int argc, char const *argv[])
{
  Robot bot = Robot("botpp", "testing");
  bot.connect(6667, "130.159.42.114");
  // while (true) {
  //   std::string reply = socket.read_line();
  //   std::cout << reply << std::endl;
  // }
  return 0;
}

