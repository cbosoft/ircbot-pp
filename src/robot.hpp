#pragma once
#include <sstream>
#include <regex>

#include "socket.hpp"

typedef struct _Message {
  std::string nick;
  std::string user;
  std::string host;
  std::string chan;
  std::string body;
} Message;
#include "command.hpp"

class Robot {
  private:
    Socket socket;
    std::string nickname;
    std::string channel;
    const std::regex is_message_regex = std::regex(":(.+)!(.+)@(.+) PRIVMSG #(.+) :\\s*(.+)");
    Message *parse_message(std::string input);
    std::list<Command *> commands;



  public:
    Robot(std::string nickname, std::string channel);
    void connect(int port, std::string address);
    void run();
    void handle_input(std::string input);
};
