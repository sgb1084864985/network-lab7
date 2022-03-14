// ClientSocket.h
#pragma once
#include <winsock2.h>
#include <string>
class ClientSocket{
public:
    SOCKET s;
    SOCKADDR_IN addr;
    ClientSocket(SOCKET s,SOCKADDR_IN addr);
    ClientSocket();
    // ClientSocket(ClientSocket&& c);

    SOCKET getSocket();
    int operator ==(const ClientSocket&c);
    const ClientSocket& operator= (ClientSocket&);
    std::string getIP();
    int getPort();
};