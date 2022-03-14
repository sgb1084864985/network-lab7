// ListClient.cpp

#include "lists.h"

void ListClient::add(ClientSocket&c){
    lck.lock();
    lstClient.push_back(c);
    lck.unlock();
}

void ListClient::remove(ClientSocket&c){
    lck.lock();
    lstClient.remove(c);
    lck.unlock();
}

void ListClient::consume(std::function<void(ClientSocket&)> fn){
    lck.lock();
    for(auto&item:lstClient){
        fn(item);
    }
    lck.unlock();
}
