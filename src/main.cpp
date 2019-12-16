#include <iostream>
#include <string>
#include <sstream>

#include "robot.hpp"

int main(int argc, char const *argv[])
{
  std::string channel = "general";

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--testing") == 0) {
      channel = "testing";
    }
    else {
      std::cout << "unrecognised argument: " << argv[i] << std::endl;
    }
  }

  Robot bot = Robot("botpp", channel);
  bot.connect(6667, "130.159.42.114");
  bot.run();
  return 0;
}

