CXX = g++
CFLAGS = -g -Wall -Wextra
OBJ = \
			obj/robot.o\
			obj/message.o\
			obj/commands/ping.o\
			obj/afk.o\
			obj/log.o\
			obj/parse.o\
			obj/socket.o
LINK = 

obj/%.o: src/%.cpp
	mkdir -p `dirname $@`
	$(CXX) $(CFLAGS) $< -c -o $@

ircbot: obj/main.o $(OBJ)
	$(CXX) $(CFLAGS) obj/main.o $(OBJ) -o $@ $(LINK)

clean:
	rm -rf obj ircbot
