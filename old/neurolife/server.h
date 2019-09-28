#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <thread>

using namespace std;

#define PORT 8080

#ifndef LINUX
#define LINUX
#endif

#ifdef WINDOWS
#include <winsock2.h>
#endif
#ifdef LINUX
using SOCKET = int;
#endif // LINUX

struct ClientConnection
{
  public:
	ClientConnection(SOCKET sock);
	~ClientConnection();

	void delay() { updated = false; }
	bool isUpdated() const { return updated; }
	void update() { updated = true; }

	SOCKET getSock() const{ return sock; }

protected:
	SOCKET sock;
	bool updated;
};

class Server
{
  public:
	
	Server();
	~Server();
	
	void run();

	void receive(string& msg, SOCKET client);
	void send(const string& msg, SOCKET client);

	void delayClients();

	void broadcast(const string& msg);
	void sync();

	string getMessage() const { return message; }

protected:
    int opt = 1;

	SOCKET server;
	vector<ClientConnection> connections;

	string message;

	thread acceptThread;
	thread servantThread;

	void accept();
	void process();
};