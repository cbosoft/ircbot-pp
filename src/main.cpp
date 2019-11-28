#include <iostream>
#include <string>
#include <sstream>

#include "robot.hpp"

int main(int argc, char const *argv[])
{
  Robot bot = Robot("botpp", "testing");
  bot.connect(6667, "130.159.42.114");
  bot.run();
  return 0;
}

