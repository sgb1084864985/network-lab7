// Server.cpp

#include <stdlib.h>
#include <WinSock2.h>
#include <stdexcept>
#include <thread>
#include <iostream>
#include "Server.h"
#include "ServerFunctions.h"

using std::cout;
using std::endl;

Server::Server(int port):sf(*this),sl(*this){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        throw std::runtime_error("wsa failure");
    }
    SOCKADDR_IN servAddr;

    servSocket=socket(PF_INET,SOCK_STREAM,0);
    if(servSocket==INVALID_SOCKET){
        throw std::runtime_error("invalid socket");
    }

    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(port);

    if(bind(servSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        throw std::runtime_error("bind failure");
    }

    if(listen(servSocket,5)==SOCKET_ERROR){
        throw std::runtime_error("listen failure");
    }

    for(int i=0;i<NumberOfThreads;i++){
        tasks[i].addListener(getListener());
        tasks[i].addFreeList(lstFreeClient);
    }
    
    sendtask.addMessageQueue(msgQ);

    std::cout<<"initialized"<<std::endl;
}

Listener& Server::getListener(){
    return sl;
}

Server::~Server(){
    closesocket(servSocket);
    WSACleanup();
    std::cout<<"server closed"<<std::endl;
}

Server::ServListener::ServListener(Server&s):s(s){}

void Server::run(){
    SOCKADDR_IN clntAddr;

    int clntAddrSize=sizeof(clntAddr);
    for(int i=0;i<NumberOfThreads;i++){
        tasks[i].start();
    }
    sendtask.start();

    // std::cout<<"start accepting"<<std::endl;
    while(running){
        SOCKET ClntSock=accept(servSocket,(SOCKADDR*)&clntAddr,&clntAddrSize);
        if(ClntSock==-1){
            throw std::runtime_error("accept failure");
        }

        addSocket(ClientSocket(ClntSock,clntAddr));
        std::cout<<"new client"<<std::endl;
    }
    cout<<"server running to end"<<endl;
    for(auto&task:tasks) {
        task.end();
        task.join();
    }
    sendtask.end();
    sendtask.join();
}

void Server::removeSocket(ClientSocket&& s){
    lstClient.remove(s);
}
void Server::addSocket(ClientSocket&& s){
    lstClient.add(s);
    lstFreeClient.push(s);
}

void Server::stop(){
    running=false;
}

void Server::ServListener::processMessage(Message& m,ClientSocket& c){
    s.sf.processMessage(m,c);
}

void Server::ServListener::stop(ClientSocket& c){
    closesocket(c.getSocket());
    s.lstClient.remove(c);
}


