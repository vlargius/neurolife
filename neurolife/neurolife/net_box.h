#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>

using namespace std;

#define PORT 2020

class NetBox {
  public:

    virtual void init(const string& ip) = 0;

    void send(const string& msg) {
        ::sendto(sock, &msg[0], msg.size(), MSG_CONFIRM, (sockaddr *)&remoteAddr, sizeof(remoteAddr));
    }

    void recv(string &msg) {
        const int maxLine = 1024;
        char buffer[maxLine];
        int n = recvfrom(sock, buffer, maxLine, MSG_WAITALL, (sockaddr *)&remoteAddr, &len);
        msg.append(buffer, n);
    }

    int getSock() const {return sock;}

  protected:
    int sock;
    socklen_t len;
    sockaddr_in remoteAddr;
};

class ServerBox : public NetBox {
  public:
    void init(const string& ip) override {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        memset(&remoteAddr, 0, sizeof(remoteAddr));
        memset(&selfAddr, 0, sizeof(selfAddr));

        selfAddr.sin_family = AF_INET;
        selfAddr.sin_addr.s_addr = INADDR_ANY;
        selfAddr.sin_port = htons(PORT);

        bind(sock, (sockaddr *)&selfAddr, sizeof(selfAddr));

        cout << "server started" << endl;
    }

  protected:
    sockaddr_in selfAddr;
};

class ClientBox : public NetBox {
    public:
    void init(const string& ip) override {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        memset(&remoteAddr, 0, sizeof(remoteAddr));
        remoteAddr.sin_family = AF_INET;
        inet_pton(AF_INET, ip.c_str(), &(remoteAddr.sin_addr.s_addr));
        remoteAddr.sin_port = htons(PORT);
    }
};
