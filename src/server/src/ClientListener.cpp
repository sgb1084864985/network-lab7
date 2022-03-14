// ClientListener.cpp

#include "ClientListener.h"
#include <iostream>

ClientListener::ClientListener(Client&c):c(c){

}
void ClientListener::stop(ClientSocket& c){
    this->c.stop();
}
void ClientListener::processMessage(Message&m,ClientSocket&c){
    if(m.len>0){
        std::cout<<m.data<<std::endl;
    }
}