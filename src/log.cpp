#include <sstream>
#include <fstream>

#include "robot.hpp"


void Robot::log(std::string s)
{
  std::stringstream ss;
  time_t raw_time = std::time(NULL);
  struct tm *timeinfo = std::localtime(&raw_time);
  char buf[100];
  strftime(buf, 99, "%Y-%m-%d.txt", timeinfo);
  const char *home = getenv("HOME");
  ss << home << "/.ircbot_log_" << buf;
  std::string path = ss.str();
  std::ofstream log_stream(path, std::ios::app);
  log_stream << s << std::endl;
}
