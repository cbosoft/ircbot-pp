#pragma once
#include <sstream>
#include <regex>
#include <list>
#include <map>

#include "socket.hpp"
#include "command.hpp"
#include "message.hpp"

class Robot {
  private:
    Socket socket;
    std::string nickname;
    std::string channel;
    const std::regex is_message_with_tag_regex = std::regex(":(.+)!(.+)@(.+) PRIVMSG #(.+) :\\s*(.+(@\\S+).+)");
    const std::regex is_message_regex = std::regex(":(.+)!(.+)@(.+) PRIVMSG #(.+) :\\s*(.+)");
    const std::regex get_tag_regex = std::regex("@(\\S+)");
    Message *parse_message(std::string input);
    std::map<std::string, std::pair<std::string, time_t>> afk_log;

    std::list<Command *> commands;



  public:
    Robot(std::string nickname, std::string channel);
    ~Robot();
    void connect(int port, std::string address);
    void run();
    void handle_input(std::string input);
    void maybe_send(std::string s);
    void send_message(std::string s);
    void log(std::string s);
};
