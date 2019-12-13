#include "message.hpp"
#include "robot.hpp"

void Robot::afk_check(Message *message)
{
  if (this->afk_log.find(message->nick) != this->afk_log.end()) {
    std::stringstream ss;
    ss << "Welcome back, " << message->nick << ".";
    this->send_message(ss.str(), message->nick);
    ss.str("");
    
    AFK_Info *afk_info = this->afk_log[message->nick];
    if (afk_info->missed_messages.size() > 0) {
      ss 
        << "While you were away you missed " 
        << afk_info->missed_messages.size()
        << " messages:";
      this->send_message(ss.str(), message->nick);

      for (std::string missed : afk_info->missed_messages) {
        ss.str("");
        ss << "  " << missed;
        this->send_message(ss.str());
      }
    }

    this->afk_log.erase(message->nick);

  }
}


bool Robot::maybe_set_afk(Message *message)
{
  std::smatch match;
  if (std::regex_search(message->body, match, this->afk_command_regex)) {
    AFK_Info *afk_info = new AFK_Info;
    afk_info->reason = match[1];
    afk_info->since = std::time(NULL);
    this->afk_log[message->nick] = afk_info;
    std::stringstream ss;
    ss << "User \"" << message->nick << "\" is now away";
    if (afk_info->reason.size() > 0)
      ss << " because \"" << afk_info->reason << "\"";
    ss << ".";
    this->send_message(ss.str());
    return true;
  }

  return false;
}


void Robot::register_missed_message(Message *message)
{
  if (message->tag.size() >= 1) {
    std::smatch match;
    if (std::regex_match(message->body, match, this->get_tag_regex)) {
      if ( this->afk_log.find(match[1]) != this->afk_log.end() ) {
        std::stringstream ss;
        AFK_Info* afk_info = afk_log[match[1]];
        std::string reason = afk_info->reason;
        time_t raw_time = afk_info->since;
        struct tm *timeinfo = std::localtime(&raw_time);
        afk_info->missed_messages.push_back(message->body);
        char buf[100];
        strftime(buf, 99, "%c", timeinfo);
        ss << "I'm sorry, " << message->nick << ", but " << match[1] << " has been AFK since " << buf;
        if (reason.size() > 0)
          ss << " because \"" << reason << "\"";
        ss << ".";
        this->send_message(ss.str());
      }
    }
  }
}
