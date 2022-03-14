// lists.h
#pragma once
#include "ClientSocket.h"
#include "Message.h"

#include <mutex>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>
class FreeClient{
    std::mutex lckSrc;
    std::condition_variable_any cv;
    std::vector<ClientSocket> lstFreeClient;
public:
    void push(ClientSocket& s);
    bool isNoEmpty();
    ClientSocket pop();
};

class MessageQueue{
    std::mutex lckSrc;
    std::condition_variable_any cv;
    std::queue<std::pair<Message,ClientSocket>> m_msgQ;
    bool int_signal=false;
    public:
    void push(Message& s,ClientSocket&c);
    bool isNoEmpty();
    bool isInterrupted();
    void interrupt();
    void interrupt_recover();
    std::pair<Message,ClientSocket> pop();
};

class ListClient{
    std::list<ClientSocket> lstClient;
    std::mutex lck;
public:
    void add(ClientSocket& s);
    void remove(ClientSocket& s);
    void consume(std::function<void(ClientSocket&)> fn);
};