// ClientSocket.cpp
#include "ClientSocket.h"

ClientSocket::ClientSocket():s(INVALID_SOCKET){}
ClientSocket::ClientSocket(SOCKET s,SOCKADDR_IN addr):s(s),addr(addr){}

SOCKET ClientSocket::getSocket(){
    return s;
}

int ClientSocket::operator==(const ClientSocket&c){
    return s==c.s;
}

const ClientSocket& ClientSocket::operator=(ClientSocket&c){
    s=c.s;
    addr=c.addr;
    return *this;
}

std::string ClientSocket::getIP(){
    return inet_ntoa(addr.sin_addr);
}


int ClientSocket::getPort(){
    return ntohs(addr.sin_port);
}


// ClientSocket::ClientSocket(ClientSocket&&c){
//     s=c.s;
//     addr=c.addr;
// }