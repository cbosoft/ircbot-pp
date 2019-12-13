#include <regex>

#include "../command.hpp"
#include "../message.hpp"

class Restart_Command : virtual public Command {
  private:
    const std::string admin = "chris@Clk-C32B2A71.chemeng.strath.ac.uk";
    const std::regex regex = std::regex("!restart");
  public:
    bool match(Message *message);
    std::string execute();
};
