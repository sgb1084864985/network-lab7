// MessageQueue.cpp
#include "lists.h"
void MessageQueue::push(Message& s,ClientSocket& c){
    lckSrc.lock();
    cv.notify_one();
    m_msgQ.push(std::pair<Message,ClientSocket>(s,c));
    lckSrc.unlock();
}

std::pair<Message,ClientSocket> MessageQueue::pop(){
    std::pair<Message,ClientSocket> ret;

    lckSrc.lock();
    while(!isNoEmpty() && !isInterrupted()){
        cv.wait(lckSrc);
    }
    if(!isInterrupted()){
        ret.first=m_msgQ.back().first;
        ret.second=m_msgQ.back().second;
    }
    else{
        interrupt_recover();
    }
    m_msgQ.pop();
    lckSrc.unlock();
    return ret;    
}

bool MessageQueue::isInterrupted(){
    return int_signal;
}
void MessageQueue::interrupt(){
    lckSrc.lock();
    cv.notify_all();
    int_signal=true;
    lckSrc.unlock();
}
void MessageQueue::interrupt_recover(){
    int_signal=false;
}

bool MessageQueue::isNoEmpty(){
    return m_msgQ.size()>0;
}