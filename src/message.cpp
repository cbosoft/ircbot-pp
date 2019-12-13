#include "robot.hpp"


Message *Robot::parse_message(std::string input)
{
  Message *rv = NULL;

  std::smatch m;
  if ((not std::regex_match(input, m, this->is_message_with_tag_regex)) && (not std::regex_match(input, m, this->is_message_regex))) {
    return NULL;
  }

  rv = new Message;

  rv->nick = m[1];
  rv->user = m[2];
  rv->host = m[3];
  rv->chan = m[4];
  rv->body = m[5];

  if (m.size() > 6) {
    rv->tag = m[6];
  }
  else {
    rv->tag = "";
  }

  return rv;
}



void Robot::maybe_send(std::string s)
{
  // if zero length, don't do anything
  if (s.size() == 0)
    return;

  // if message of substance: send
  this->send_message(s);
}




void Robot::send_message(std::string message) { this->send_message(message, this->channel); }
void Robot::send_message(std::string message, std::string to)
{
  this->log(message);

  std::stringstream ss;
  ss << "PRIVMSG " << to << " " << message << std::endl;
  std::string to_send = ss.str();
  this->socket.write(to_send);
}
