// Server.h
#pragma once
#include <WinSock2.h>
#include <map>
#include <functional>
#include "Message.h"
#include "Listener.h"
#include "lists.h"
#include "ClientSocket.h"
#include "Tasks.h"

class Server{
    static const int NumberOfThreads=3;
    int port;
    // std::list<ClientSocket> lstClient;
    // std::vector<ClientSocket> lstFreeClient;
    class ServListener : public Listener{
        Server&s;
    public:
        ServListener(Server&s);
        void processMessage(Message&m,ClientSocket&c);
        void stop(ClientSocket& c);
    };

    class ServerFunctions{
        Server& s;
        std::map<MessageType,std::function<void(Server&,Message&,ClientSocket&)>> operators;
        public:
        ServerFunctions(Server&s);
        void processMessage(Message&,ClientSocket&c);
        // static void broadcast(Server&s,Message&,ClientSocket&);
        // static void print(Server&s,Message&m,ClientSocket&);
    };


    SOCKET servSocket;
    ServerFunctions sf;
    ServListener sl;
    ReadTask tasks[NumberOfThreads];
    bool running=true;

    void removeSocket(ClientSocket&& s);
    void addSocket(ClientSocket&& s);
    SendTask sendtask;

public:
    ListClient lstClient;
    FreeClient lstFreeClient;
    MessageQueue msgQ;
    
    Server(int port=1094);
    ~Server();
    void run();
    void stop();
    Listener& getListener();
    
};


