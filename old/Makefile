CC = clang++
TARGETS = ./neurolife/*.cpp
CFLAGS = -DLINUX -pthread 
SFLAGS = -DLINUX -DSERV -pthread

all: server client

server: $(TARGETS)
	$(CC) -std=c++14 $(SFLAGS) $(TARGETS) -o ./bin/ubuntu/server
client: $(TARGETS)
	$(CC) -std=c++14 $(CFLAGS) $(TARGETS) -lSDL2 -o ./bin/ubuntu/client
sd: $(TARGETS)
	$(CC) -std=c++14 -g $(SFLAGS) $(TARGETS) -o ./bin/ubuntu/serverd
cd: $(TARGETS)
	$(CC) -std=c++14 -g $(CFLAGS) $(TARGETS) -lSDL2 -o ./bin/ubuntu/clientd
c: 
	rm -rf /bin/ubuntu/server ./bin/ubuntu/client
