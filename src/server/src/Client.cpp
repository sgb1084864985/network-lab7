// Client.cpp

#include "Client.h"
#include "ClientListener.h"

Client::Client(std::string s,int port):ptr_Listener(new ClientListener(*this)){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        throw std::runtime_error("wsa failure");
    }
    SOCKADDR_IN servAddr;

    cs.s=socket(PF_INET,SOCK_STREAM,0);
    if(cs.s==INVALID_SOCKET){
        throw std::runtime_error("invalid socket");
    }

    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(s.c_str());
    servAddr.sin_port=htons(port);

    if(connect(cs.s,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        throw std::runtime_error("connects failure");
    }
    freelist.push(cs);
    rt.addFreeList(freelist);
    rt.addListener(*ptr_Listener);
    // st.addMessageQueue(mq);

    std::cout<<"connected..."<<std::endl;
}

void Client::stop(){
    rt.end();
    running=false;
    std::cout<<"connection close"<<std::endl;
}

void Client::run(){
    int cmd;
    Message m;
    // std::string str;
    char buf[80];
    rt.start();

    std::string help = 
        "menu:\n"
        "1: show menu\n"
        "2: close client\n"
        "3: get time\n"
        "4: get server name\n"
        "5: get clients list\n"
        "6: send message\n"
        ;
    std::cout<<help;
    while(running){
        std::cout<<"> ";
        cmd=7;
        std::cin.getline(buf,sizeof(buf));
        cmd=atoi(buf);
        switch (cmd)
        {
        case 1:
            std::cout<<help;
            break;
        case 2:
            closesocket(cs.getSocket());
            running=false;
            break;
        case 3:
            m.cmd=(int)MessageType::GET_TIME;
            // for(int i=0;i<100;i++)
            m.sendMessage(cs.getSocket());
            break;
        case 4:
            m.cmd=(int)MessageType::GET_NAME;
            m.sendMessage(cs.getSocket());
            break;
        case 5:
            m.cmd=(int)MessageType::GET_CLIENTS;
            m.sendMessage(cs.getSocket());
            break; 
        case 6:
            m.cmd=(int)MessageType::DATA;
            std::cout<<"id> ";
            std::cin.getline(buf,sizeof(buf));
            if(atoi(buf)<=0) {
                std::cout<<"illegal"<<std::endl;
            }
            m.data.assign(buf);
            std::cout<<"content> ";
            std::cin.getline(buf,sizeof(buf));
            m.data.append(buf);
            m.sendMessage(cs.getSocket());
            break; 
        case 7:
            closesocket(cs.getSocket());
            running=false;
            break;        
        case 8:
            m.cmd=(int)MessageType::END;
            m.sendMessage(cs.getSocket());
            break; 
        default:
            break;
        }
    }
    rt.join();
}

Client::~Client(){
    // closesocket(cs.s);
    WSACleanup();
}