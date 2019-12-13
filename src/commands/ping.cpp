#include "ping.hpp"

std::string Ping_Command::execute() 
{
  return "PONG";
}

bool Ping_Command::match(Message *m)
{
  return std::regex_match(m->body, this->regex);
}
