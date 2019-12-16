#include <sstream>
#include <regex>

#include "../message.hpp"
#include "about.hpp"



bool About_Command::match (Message *message)
{
  return std::regex_match(message->body, this->regex);
}



std::string About_Command::execute()
{
  return "ircbot-pp: ircbot in c++. commands: !afk [reason], !restart, !about.";
}

