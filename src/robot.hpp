#pragma once
#include <sstream>
#include <regex>
#include <list>
#include <map>

#include "socket.hpp"
#include "command.hpp"
#include "message.hpp"

typedef struct _AFK_Info {
  std::vector<std::string> missed_messages;
  time_t since;
  std::string reason;
} AFK_Info;

class Robot {
  private:
    Socket socket;
    std::string nickname;
    std::string channel;
    const std::regex is_message_with_tag_regex = std::regex(":(.+)!(.+)@(.+) PRIVMSG #(.+) :\\s*(.+(@\\S+).+)");
    const std::regex is_message_regex = std::regex(":(.+)!(.+)@(.+) PRIVMSG #(.+) :\\s*(.+)");
    const std::regex get_tag_regex = std::regex("@(\\S+)");
    const std::regex afk_command_regex = std::regex("!afk\\s*(.*)");
    const std::regex error_regex = std::regex("ERROR.*");
    Message *parse_message(std::string input);
    std::map<std::string, AFK_Info *> afk_log;

    std::list<Command *> commands;

    void afk_check(Message *message);
    bool maybe_set_afk(Message *message);
    void register_missed_message(Message *message);



  public:
    Robot(std::string nickname, std::string channel);
    ~Robot();
    void connect(int port, std::string address);
    void run();
    void handle_input(std::string input);
    void maybe_send(std::string s);
    void send_message(std::string message);
    void send_message(std::string message, std::string to);
    void log(std::string s);
};
