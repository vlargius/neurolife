CC = g++
TARGETS = ./neurolife/*.cpp

all: server client

server: $(TARGETS)
	$(CC) -std=c++14 -DLINUX -DSERV $(TARGETS) -o ./bin/ubuntu/nlifes
client: $(TARGETS)
	$(CC) -std=c++14 -DLINUX -DCLI $(TARGETS) -lSDL2 -o ./bin/ubuntu/nlifec
sd: $(TARGETS)
	$(CC) -std=c++14 -g -DLINUX -DSERV $(TARGETS) -o ./bin/ubuntu/nlifes
cd: $(TARGETS)
	$(CC) -std=c++14 -g -DLINUX -DCLI $(TARGETS) -lSDL2 -o ./bin/ubuntu/nlifec
c: 
	rm -rf /bin/ubuntu/nlife