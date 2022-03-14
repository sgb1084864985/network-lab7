// Message.h
#pragma once
#include <WinSock2.h>
#include <string>
enum class MessageType{
    START,DATA,END,HEART,
    ECHO,PRINT,BROADCAST,
    GET_TIME,GET_LIST,GET_CLIENTS,GET_NAME
};
class Message{
public:
    // enum typeCMD{START,DATA,END,HEART};
    int cmd;
    int len=0;
    static const int MAX_BUF_CNT=1024;
    std::string data;
    boolean readMessage(SOCKET s);
    static void recv_n_byte(SOCKET s,char* buf,int n_byte);
    void sendMessage(SOCKET s);
    Message();
    Message(int cmd);
    Message(const std::string& s,int cmd=(int)MessageType::DATA);
    void setData(std::string&s);
};
