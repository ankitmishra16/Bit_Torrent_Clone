CC = g++
CFLAGS = -g -Wall -std=c++1z -w
DEPS = global.h
OBJ = to_tracker_1.o Main.o bin2hex.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< -lcrypto

Main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lcrypto