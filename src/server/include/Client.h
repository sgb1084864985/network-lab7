// Client.h
#pragma once
#include "ClientSocket.h"
#include "Message.h"
#include "Tasks.h"
#include "lists.h"
#include "Listener.h"
#include <iostream>
#include <stdexcept>

#include <string>
class Client{
    ClientSocket cs;
    ReadTask rt;
    bool running;
    // SendTask st;
    // MessageQueue mq;
    FreeClient freelist;
    std::shared_ptr<Listener> ptr_Listener;
    public:
    Client(std::string s,int port);

    void run();
    void stop();

    ~Client();
};

// int main(){
//     Client c("10.192.172.162",8086);
//     c.run();
// }