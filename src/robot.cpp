#include <regex>
#include <ctime>
#include <ios>
#include <fstream>

#include "robot.hpp"
#include "socket.hpp"
#include "exception.hpp"
#include "message.hpp"

#include "commands/ping.hpp"
#include "commands/restart.hpp"
#include "commands/about.hpp"




Robot::Robot(std::string nickname, std::string channel)
{
  std::stringstream ss;
  ss << "#" << channel;
  this->channel = ss.str();
  this->nickname = nickname;

  // this->commands.push_back(new xyz_Command());
  this->commands.push_back(new Ping_Command());
  this->commands.push_back(new Restart_Command());
  this->commands.push_back(new About_Command());
}





Robot::~Robot()
{
  //for (auto command_ptr : this->commands) {
  //  delete command_ptr;
  //}
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
  ss << "JOIN " << this->channel << std::endl;
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
    catch (const ServerException& ex) {
      // exit on server error
      std::cout << ex.what() << std::endl;
      exit(1);
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




void Robot::handle_input(std::string input)
{
  this->log(input);

  if (std::regex_match(input, this->error_regex)) {
    throw ServerException(input);
  }

  Message *message = this->parse_message(input);

  if (message == NULL) {
    if (input.find("PING") != std::string::npos) {
      std::string pong = std::string(input);
      pong.replace(1, 1, "O");
      this->socket.write(pong);
    }
    return;
  }

  if (message->body[0] == '!') {
    if (not this->maybe_set_afk(message)) {
      for (auto command_ptr : this->commands) {
        if (command_ptr->match(message)) {
          this->maybe_send(command_ptr->execute());
        }
      }
    }
  }

  delete message;
}
