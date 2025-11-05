CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
PTHREAD_LIB = -pthread

.PHONY: all server client clean

all: server client

server: server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server $(PTHREAD_LIB)

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client $(PTHREAD_LIB)

clean:
	rm -f server client