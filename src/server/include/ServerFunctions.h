// SeverFunctions.h
#pragma once
#include "Message.h"
#include "Server.h"
#include <string>

namespace ServerFuncs{
    void broadcast(Server&s,Message&,ClientSocket&);
    void print(Server&s,Message&m,ClientSocket&);
    void echo(Server&s,Message&m,ClientSocket&);
    void time(Server&s,Message&m,ClientSocket&);
    void name(Server&s,Message&m,ClientSocket&);
    void list(Server&s,Message&m,ClientSocket&);
    void stop(Server&s,Message&m,ClientSocket&);
    void send(Server&s,Message&m,ClientSocket&);
};


// namespace ServerFuncs{
//     class ServFunctional{
//         virtual void operator() (Server&s,Message&m,ClientSocket&c)=0;
//         virtual std::string getName()=0;
//         virtual void printInfo();
//     };

//     class Print : public ServFunctional{
//         void operator() (Server&s,Message&m,ClientSocket&c);
//         std::string getName();
//     };

//     class Echo : public ServFunctional{
//         void operator() (Server&s,Message&m,ClientSocket&c);
//         std::string getName();
//         virtual void printInfo();

//     };
// };


