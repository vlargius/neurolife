#include "client.h"

#ifdef  LINUX

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client() :
	sock(0) {}

Client::~Client() {}

void Client::connect() {
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

void Client::send(const string& msg) {
	::send(sock, &msg[0], msg.size(), 0);
}

void Client::receive(string& msg) {
	int valread;
	char buffer[1024] = { 0 };
	valread = read(sock, buffer, 1024);
	msg = buffer;
}

#endif //  LINUX

#ifdef WINDOWS

#include <winsock2.h>
#include <Ws2tcpip.h>

Client::Client() :
	sock(0),
	opt(0) {}

Client::~Client() {}

bool Client::connect() {
	SOCKADDR_IN addr;
	WSADATA WSAData;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (inet_pton(AF_INET, ip.c_str(), &(addr.sin_addr)) <= 0) {
		printf("\n inet_pton error occured\n");
		return false;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	if (::connect(sock, (SOCKADDR *)&addr, sizeof(addr)) != 0)
	{
		cout << "Client: connect() failed! Error code: " << WSAGetLastError() << endl;
		return false;
	}
	cout << "Connected to server!" << endl;
	return true;
}

void Client::send(const string& msg) {
	::send(sock, &msg[0], msg.size(), 0);
}

void Client::receive(string& msg) {
	int valread;
	char buffer[1024] = { 0 };
	valread = ::recv(sock, buffer, 1024, opt);
	msg = buffer;
}

#endif //WINDOWS