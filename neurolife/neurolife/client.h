// Client side C/C++ program to demonstrate Socket programming 
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define PORT 8080 

using namespace std;

class Client {
public:
	Client():
			sock(0) {}

	void init(const string& ip) {
			this->ip = ip;
	}

	void connect() {
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	printf("\n Socket creation error \n");
    	}

		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		// Convert IPv4 and IPv6 addresses from text to binary form
		if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
			printf("\nInvalid address/ Address not supported \n");
		}

		if (::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
			printf("\nConnection Failed \n");
		}
	}

	void send(const string& msg) {
		::send(sock , &msg[0] , msg.size() , 0);
	}

	void receive(string& msg) {
		int valread;
		char buffer[1024] = {0};
    	valread = read(sock , buffer, 1024);
		msg = buffer;
	}

  protected:
	string ip;
	
	sockaddr_in address;
	sockaddr_in serv_addr;
	int sock;	
};
