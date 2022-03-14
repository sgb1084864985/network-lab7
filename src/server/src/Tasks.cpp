// Tasks.cpp
#include "Tasks.h"
#include <thread>
#include <iostream>
void ReadTask::run(){
    // std::cout<<"start task"<<std::endl;
    while(running){
        ClientSocket wSocket = freeLst->pop();
        // std::cout<<"new socket allocated"<<std::endl;
        while(socket_task_running){
            Message msg;
            if(msg.readMessage(wSocket.getSocket())){
                for(auto& l:lstListener){
                    l.get().processMessage(msg,wSocket);
                }
            }
            else{
                for(auto& l:lstListener){
                    l.get().stop(wSocket);
                    stop_socket_task();
                    std::cout<<"socket closed"<<std::endl;
                }
            }
        }
    }
}

void Task::join(){
    if(th.joinable())th.join();
}

void Task::end(){
    running=false;
}

void Task::start(){
    th = std::thread(&run,std::ref(*this));
}

void ReadTask::addListener(Listener& l){
    lckListener.lock();
    lstListener.push_back(l);
    lckListener.unlock();
}

void ReadTask::addFreeList(FreeClient& FreeLst){
    freeLst=&FreeLst;
}

void ReadTask::stop_socket_task(){
    socket_task_running=false;
}

ReadTask::ReadTask(){

}

void SendTask::addMessageQueue(MessageQueue& q){
    mq=&q;
}

void SendTask::run(){
    while(running){
        auto p = mq->pop();
        if(!running) break;
        p.first.sendMessage(p.second.getSocket());
    }
}