#include "server.h"

#ifdef LINUX

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>


Server::Server() {}

Server::~Server() {}

void Server::run() {
	addrlen = sizeof(address);
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		cerr << "socket failed";
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		&opt, sizeof(opt))) {
		cerr << "setsockopt";
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		cerr << "bind failed";
		exit(EXIT_FAILURE);
	}

	accept();
}

void Server::receive(string& msg) {
	char buffer[1024]{ 0 };
	int valread = ::read(new_socket, buffer, sizeof(buffer));
	msg = buffer;
}

void Server::send(const string& msg) {
	::send(new_socket, msg.c_str(), msg.size(), 0);
}

void Server::accept() {
	if (listen(server_fd, 3) < 0) {
		cerr << "listen";
		exit(EXIT_FAILURE);
	}
	if ((new_socket = ::accept(server_fd, (struct sockaddr *)&address,
		(socklen_t *)&addrlen)) < 0) {
		cerr << "accept";
		exit(EXIT_FAILURE);
	}
}

#endif // LINUX


#ifdef WINDOWS

Server::Server() {}

Server::~Server() {
	closesocket(client);
	cout << "Client disconnected." << endl;
}

void Server::run() {
	WSADATA WSAData;
	SOCKADDR_IN serverAddr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	accept();
}

void Server::receive(string& msg) {
	int valread;
	char buffer[1024] = { 0 };
	valread = ::recv(client, buffer, 1024, 0);
	msg = buffer;
}

void Server::send(const string& msg) {
	::send(client, &msg[0], msg.size(), 0);
}

void Server::accept() {
	listen(server, 0);

	cout << "Listening for incoming connections..." << endl;

	int clientAddrSize = sizeof(clientAddr);
	client = ::accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize);
}

#endif //WINDOWS