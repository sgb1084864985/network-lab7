// Tasks.h
#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include "Listener.h"
#include "Message.h"
#include "lists.h"

class Task{
protected:
    std::thread th;
    bool running=true;
    virtual void run()=0;
public:
    virtual void start();
    virtual void end();
    virtual void join();
};

class ReadTask : public Task{
    std::mutex lckListener;
    std::vector<std::reference_wrapper<Listener>> lstListener;
    FreeClient* freeLst=nullptr;
    bool socket_task_running=true;
    void run();
public:
    ReadTask();
    void addListener(Listener& l);
    void addFreeList(FreeClient& FreeLst);
    void stop_socket_task();
};

class SendTask : public Task{
    MessageQueue* mq;
    void run();
public:
    void addMessageQueue(MessageQueue& q);
};
