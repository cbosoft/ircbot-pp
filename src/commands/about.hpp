#include <regex>

#include "../command.hpp"
#include "../message.hpp"

class About_Command : virtual public Command {
  private:
    const std::regex regex = std::regex("!about");
  public:
    bool match(Message *message);
    std::string execute();
};

