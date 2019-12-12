#pragma once
#include <string>

typedef struct _Message {
  std::string nick;
  std::string user;
  std::string host;
  std::string chan;
  std::string body;
  std::string tag;
} Message;
