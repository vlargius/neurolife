#pragma once

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define PORT 8080

#ifdef WINDOWS
#include <winsock2.h>
#endif

class Server {
public:
	
	Server();
	~Server();
	
	void run();

	void receive(string& msg);
	void send(const string& msg);

protected:

    int server_fd;
    int new_socket;
    int opt = 1;

	SOCKET server, client;
	SOCKADDR_IN clientAddr;

	void accept();
};