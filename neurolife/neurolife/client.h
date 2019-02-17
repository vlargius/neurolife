#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define PORT 8080 

class Client {
public:
	Client();
	~Client();

	void init(const string& ip) {
			this->ip = ip;
	}

	bool connect();

	void send(const string& msg);

	void receive(string& msg);

  protected:
	string ip;
	int sock;
	int opt;
};