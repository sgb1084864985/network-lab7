#include "Message.h"
#include <iostream>

void Message::recv_n_byte(SOCKET s,char* buf,int n_byte){
    int read_len;
    while(n_byte>0){
        read_len=recv(s,buf,n_byte,0);
        if(read_len<=0) throw -1;
        buf+=read_len;
        n_byte-=read_len;
    }
}

boolean Message::readMessage(SOCKET s){
    try{
        recv_n_byte(s,(char*)&cmd,sizeof(int));
        recv_n_byte(s,(char*)&len,sizeof(int));
        if(len>0){
            char buf[MAX_BUF_CNT];
            recv_n_byte(s,buf,len);
            data.assign(buf,len);
        }
    }
    catch(int ex){
        // std::cout<<"read message failed"<<std::endl;
        return false;
    }
    return true;
}

void Message::sendMessage(SOCKET s){
    len=data.length();
    send(s,(char*)&cmd,sizeof(int),0);
    send(s,(char*)&len,sizeof(int),0);
    if(len>0)send(s,data.c_str(),len,0);
}

Message::Message(){}
Message::Message(int cmd):cmd(cmd){
}

Message::Message(const std::string& s,int cmd):cmd(cmd),data(s),len(s.size()){

}

void Message::setData(std::string&s){
    len=s.size();
    data=s;
}