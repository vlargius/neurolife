#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <thread>

using namespace std;

#define PORT 8080

#ifdef WINDOWS
#include <winsock2.h>
#endif
#ifdef LINUX
using SOCKET = int;
#endif // LINUX


class Server {
public:
	
	Server();
	~Server();
	
	void run();

	void receive(string& msg, SOCKET client);
	void send(const string& msg, SOCKET client);

	void broadcast(const string& msg);
	void sync();

protected:
    int opt = 1;

	SOCKET server;
	vector<SOCKET> clients;

	thread acceptThread;

	void accept();
};