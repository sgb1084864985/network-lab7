#include "Client.h"

int main(int argc,char* argv[]){
    char addrIPv4[64]="127.0.0.1";
    int port=1094;
    if(argc<=1){
        std::cout<<"you have not put IP address, so default is 127.0.0.1"<<std::endl;
    }
    else{
        strcpy(addrIPv4,argv[1]);
    }

    if(argc<=2){
        std::cout<<"you have not put port, so default is 1094"<<std::endl;
    }
    else{
        port=atoi(argv[2]);
    }

    Client c(addrIPv4,port);
    c.run();
}