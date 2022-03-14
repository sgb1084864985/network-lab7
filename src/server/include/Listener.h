// Listener.h
#pragma once
#include "Message.h"
#include "ClientSocket.h"
class Listener{
public:
    virtual void stop(ClientSocket& c)=0;
    virtual void processMessage(Message&,ClientSocket&c)=0;
};