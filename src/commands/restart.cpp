#include <sstream>
#include <regex>

#include "../message.hpp"
#include "restart.hpp"



bool Restart_Command::match (Message *message)
{
  if (std::regex_match(message->body, this->regex)) {
    std::stringstream ss;
    ss << message->user << "@" << message->host;
    std::string user_string = ss.str();
    if (this->admin.compare(user_string) == 0)
      return true;
  }

  return false;
}



std::string Restart_Command::execute()
{
  exit(0);
}
