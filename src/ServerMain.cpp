#include "Server.h"
#include <iostream>
int main(int argc,char* argv[]){
    int port=1094;
    if(argc<=1){
        std::cout<<"you have not put port. default port is 1094."<<std::endl;
    }
    else{
        port=atoi(argv[1]);
    }

    Server s(port);
    s.run();
}