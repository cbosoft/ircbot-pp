CXX = g++
CFLAGS = -g -Wall -Wextra
OBJ = \
			obj/robot.o\
			obj/socket.o
LINK = 

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CFLAGS) $< -c -o $@

ircbot: obj/main.o $(OBJ)
	$(CXX) $(CFLAGS) obj/main.o $(OBJ) -o $@ $(LINK)

clean:
	rm -rf obj ircbot
