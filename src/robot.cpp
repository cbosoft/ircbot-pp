#include <regex>

#include "robot.hpp"
#include "socket.hpp"
#include "exception.hpp"

Robot::Robot(std::string nickname, std::string channel) {
  this->channel = channel;
  this->nickname = nickname;
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
    catch (TimeoutException ex) {
      // ignore timeout stuff
    }
    catch (Exception ex) {
      // other exceptions: print but don't exit
      ex.print();
    }

  }
}

void Robot::handle_input(std::string input)
{
  // TODO
}
