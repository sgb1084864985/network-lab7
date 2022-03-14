// ServerFuncitions.cpp
#include "Server.h"
#include "ServerFunctions.h"
#include <iostream>
#include <ctime>
#include <sstream>

Server::ServerFunctions:: ServerFunctions(Server&s):s(s){
    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::DATA,ServerFuncs::send)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::ECHO,ServerFuncs::echo)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::BROADCAST,ServerFuncs::broadcast)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::GET_TIME,ServerFuncs::time)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::GET_CLIENTS,ServerFuncs::list)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::END,ServerFuncs::stop)
    );

    operators.insert(
        std::pair<MessageType,std::function<void(Server&,Message&,ClientSocket&)>>
        (MessageType::GET_NAME,ServerFuncs::name)
    );
}

void Server::ServerFunctions::processMessage(Message&m,ClientSocket&c){
    operators[(MessageType)m.cmd](s,m,c);
}

void ServerFuncs::broadcast(Server&s,Message&m,ClientSocket&c){
    std::cout<<"request broadcast:"<<std::endl;
    std::cout<<m.data<<std::endl;
    auto func = [&m,&s](ClientSocket& cs){
        s.msgQ.push(m,cs);
    };
    s.lstClient.consume(func);
}

void ServerFuncs::print(Server&s,Message&m,ClientSocket&c){
    std::cout<<"request print:"<<std::endl;
    std::cout<<m.data<<std::endl;
}

void ServerFuncs::echo(Server&s,Message&m,ClientSocket&c){
    std::cout<<"request echo:"<<std::endl;
    std::cout<<m.data<<std::endl;
    // m.sendMessage(c.getSocket());
    s.msgQ.push(m,c);
}

void ServerFuncs::time(Server&s,Message&m,ClientSocket&c){
    // std::cout<<"request time:"<<std::endl;
    std::ostringstream os;
    os<<"request time: "<<::time(nullptr);
    Message msg(os.str(),(int)MessageType::GET_TIME);
    s.msgQ.push(msg,c); 
}

void ServerFuncs::list(Server&s,Message&m,ClientSocket&c){
    // std::cout<<"request list:"<<std::endl;
    std::ostringstream os;
    auto func = [&os](ClientSocket& cs){
        os<<"Client Infomation| id: "<<cs.s<<" IP: "<<cs.getIP()<<" port: "<<cs.getPort()<<"\n";
    };
    s.lstClient.consume(func);
    std::cout<<os.str()<<std::endl;
    Message msg(os.str(),(int)MessageType::GET_CLIENTS);
    s.msgQ.push(msg,c); 
}

void ServerFuncs::stop(Server&s,Message&m,ClientSocket&c){
    s.stop();
}

void ServerFuncs::send(Server&s,Message&m,ClientSocket&c){
    // std::cout<<"request send:"<<std::endl;
    std::istringstream is(m.data);
    std::ostringstream os;
    SOCKET toSend;
    char str[300];
    is>>toSend;
    is.getline(str,sizeof(str));

    os<<"send message: "<<std::endl;
    os<<"Client Infomation| id: "<<c.s<<" IP: "<<c.getIP()<<" port: "<<c.getPort()<<std::endl;
    os<<"send info: "<<std::endl;
    os<<str;

    // std::cout<<toSend<<" "<<os.str()<<std::endl;

    Message msg(os.str(),(int)MessageType::DATA);
    auto func = [&s,&msg,toSend](ClientSocket& cs){
        if(toSend==cs.s){
            s.msgQ.push(msg,cs);
            // std::cout<<"sent"<<std::endl;
        }
    };
    s.lstClient.consume(func);
}

void ServerFuncs::name(Server&s,Message&m,ClientSocket&c){
    std::ostringstream os;
    char buf[80];
    gethostname(buf,sizeof(buf));
    os<<"request name: "<<buf;
    Message msg(os.str(),(int)MessageType::GET_NAME);
    s.msgQ.push(msg,c);     
}

// void ServerFuncs::ServFunctional::printInfo(){
//     std::cout<<"This request is: "<<getName()<<std::endl;
// }

// void ServerFuncs::Print::operator()(Server&s,Message&m,ClientSocket&c){
//     std::cout<<m.data<<std::endl;
// }

// std::string ServerFuncs::Print::getName(){
//     return "PRINT";
// }

// void ServerFuncs::Echo::operator()(Server&s,Message&m,ClientSocket&c){
//     printInfo();
//     m.sendMessage(c.getSocket());
// }

// std::string ServerFuncs::Echo::getName(){
//     return "ECHO";
// }


