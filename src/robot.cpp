#include <regex>
#include <ctime>
#include <ios>
#include <fstream>

#include "robot.hpp"
#include "socket.hpp"
#include "exception.hpp"
#include "message.hpp"

Robot::Robot(std::string nickname, std::string channel)
{
  this->channel = channel;
  this->nickname = nickname;

  // this->commands.push_back(new xyz_Command());
}





Robot::~Robot()
{
  for (auto command_ptr : this->commands) {
    delete command_ptr;
  }
}




void Robot::connect(int port, std::string address) 
{
  this->socket = Socket(port, address);

  std::stringstream connect_msg_builder;
  connect_msg_builder << "NICK " << nickname << std::endl;
  this->socket.write(connect_msg_builder.str());

  connect_msg_builder.str("");
  connect_msg_builder << "USER " << nickname << " * 0 :bot"<< std::endl;
  socket.write(connect_msg_builder.str());

  std::regex ping("PING(.*)");

  std::cout << "Waiting for end of MOTD message indicating connection complete." << std::endl;
  while (true) {

    std::string received = this->socket.readline();

    if (received.find(":End of /MOTD") != std::string::npos) {
      break;
    }
    else if (received.find("ERROR") != std::string::npos) {
      exit(1);
    }
    else if (received.find("PING") != std::string::npos) {
      std::string pong = std::string(received);
      pong.replace(1, 1, "O");
      this->socket.write(pong);
    }

  }

  std::stringstream ss;
  ss << "JOIN #" << this->channel << std::endl;
  this->socket.write(ss.str());

  std::cout << "Joining channel #" << this->channel << std::endl;
  while (true) {

    std::string received = this->socket.readline();

    if (received.find(":End of /NAMES") != std::string::npos) {
      break;
    }
    else if (received.find("ERROR") != std::string::npos) {
      exit(1);
    }
    else if (received.find("PING") != std::string::npos) {
      std::string pong = std::string(received);
      pong.replace(1, 1, "O");
      this->socket.write(pong);
    }

  }
}





void Robot::run()
{
  while (true) {

    try {
      std::string received = socket.readline();
      this->handle_input(received);

    }
    catch (const TimeoutException& ex) {
      // ignore timeout stuff
    }
    catch (const Exception& ex) {
      // other exceptions: print but don't exit
      std::cout << ex.what() << std::endl;
    }

  }
}







Message *Robot::parse_message(std::string input)
{
  Message *rv = NULL;

  std::smatch m;
  if ((not std::regex_search(input, m, this->is_message_with_tag_regex)) || (not std::regex_search(input, m, this->is_message_regex))) {
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

void Robot::handle_input(std::string input)
{
  Message *m = this->parse_message(input);
  std::cout << "message: " << input << std::endl;
  if (m == NULL)
    return;

  if (m->body[0] == '!') {

    // TODO: do something with command

  }
  delete m;
}


void Robot::log(std::string s)
{
  std::stringstream ss;
  time_t raw_time = std::time(NULL);
  struct tm *timeinfo = std::localtime(&raw_time);
  char buf[100];
  strftime(buf, 99, "%Y-%m-%d.txt", timeinfo);
  const char *home = getenv("HOME");
  ss << home << "/.ircbot_log_" << buf;
  std::ofstream log_stream(ss.str(), std::ios::app);
  log_stream << s;
}
