#pragma once

#include <regex>
#include <iostream>

#include "../message.hpp"
#include "../command.hpp"

class Ping_Command : virtual public Command {
  private:
    const std::regex regex = std::regex("!ping");
  public:
    std::string execute();
    bool match(Message *message);
};
