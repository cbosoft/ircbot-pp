#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "socket.hpp"
#include "exception.hpp"

Socket::Socket() {
  this->timeout = 10;
}

Socket::Socket(int port, std::string address) {
  this->timeout = 10;

  struct sockaddr_in serv_addr;
  if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return;
  }

  if (connect(this->fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return;
  }

  int flags = fcntl(this->fd, F_GETFL, 0);
  fcntl(this->fd, F_SETFL, flags | O_NONBLOCK);
}






std::string Socket::readline()
{
  char ch = '\0', buf[1];
  int n_read, rlen = 0;
  std::stringstream rv_builder;
  int start_time = time(NULL), seconds_passed = 0;

  do {
    seconds_passed = time(NULL) - start_time;
    n_read = read(this->fd, buf, 1);
    if (n_read != -1) {
      ch = buf[0];
      if (ch != '\n') {
        rv_builder << ch;
        rlen ++;
      }
    }
  } while ((ch != '\n') && (seconds_passed < this->timeout));

  if (rlen == 0) {
    throw TimeoutException("Read timed out");
  }

  std::string rv = rv_builder.str();
  std::cout << "< " << rv << std::endl;
  return rv;
}




void Socket::write(std::string val)
{
  send(fd, val.c_str(), val.length(), 0);
  std::cout << "> " << val << std::endl;
}


void Socket::set_timeout(int timeout)
{ 
  this->timeout = timeout;
}
