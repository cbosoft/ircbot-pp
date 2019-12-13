#pragma once
#include <string>

#include "message.hpp"

class Command {
  public:
    virtual std::string execute() { return "WHAT"; };
    virtual bool match(Message *m) { (void)m; return true; }
};
