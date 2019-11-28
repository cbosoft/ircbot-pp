#include "robot.hpp"
#include "socket.hpp"
#include "exception.hpp"

Robot::Robot(std::string nickname, std::string channel) {
  this->channel = channel;
  this->nickname = nickname;
}




void Robot::connect(int port, std::string address) 
{
  socket = Socket(port, address);

  try {
    while (true) {
      std::cout << socket.readline() << std::endl;
    }
  }
  catch (Exception ex) {
      ex.print();
  }

  std::stringstream connect_msg_builder;
  connect_msg_builder << "NICK " << nickname << std::endl;
  socket.write(connect_msg_builder.str());

  connect_msg_builder.str("");
  connect_msg_builder << "USER " << nickname << " * 0 :bot"<< std::endl;
  socket.write(connect_msg_builder.str());

  while (true) {

    try {
      std::string received = socket.readline();
      std::cout << received << std::endl;
    }
    catch (Exception ex) {
      ex.print();
    }

  }
}
