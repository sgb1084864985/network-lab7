// FreeClient.cpp
#include "lists.h"

bool FreeClient::isNoEmpty(){
    return lstFreeClient.size()>0;
}

void FreeClient::push(ClientSocket& s){
    lckSrc.lock();
    cv.notify_one();
    lstFreeClient.push_back(s);
    lckSrc.unlock();
}

ClientSocket FreeClient::pop(){
    ClientSocket ret;
    lckSrc.lock();
    while(!isNoEmpty()){
        cv.wait(lckSrc);
    }

    ret=lstFreeClient.back();
    lstFreeClient.pop_back();
    lckSrc.unlock();
    return ret;
}