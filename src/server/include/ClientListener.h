// ClientListener.h
#pragma once
#include "Listener.h"
#include "Client.h"

class ClientListener:public Listener{
    Client& c;
public:
    ClientListener(Client&c);
    virtual void stop(ClientSocket& c);
    virtual void processMessage(Message&,ClientSocket&c);
};