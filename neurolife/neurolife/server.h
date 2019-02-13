// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <cstring>
#include <string>


using namespace std;

#define PORT 8080

class Server {
public:
    Server()
        {}

    void run() {
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
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
            cerr << "bind failed";
            exit(EXIT_FAILURE);
        }

        accept();
    }

    void receive(string& msg) {
        char buffer[1024]{0};
        int valread = ::read(new_socket , buffer, sizeof(buffer));
        msg = buffer;
    }

    void send(const string& msg) {
        ::send(new_socket, msg.c_str(), msg.size(), 0);
    }

protected:

    int server_fd;
    int new_socket; 
    sockaddr_in address; 
    int opt = 1;
    int addrlen;

    void accept() {
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

};