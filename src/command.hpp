#pragma once
#include <string>
#include <regex>

#include "message.hpp"

class Command {
  public:
    virtual ~Command () {};
    virtual std::string execute();
    virtual bool match(Message *m);
    virtual std::string on_tag(Message *m) { (void) m; return ""; }
};
