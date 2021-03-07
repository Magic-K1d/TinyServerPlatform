/*************************************************************************
  > File Name: main.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 06:24:57 PM CST
*************************************************************************/

#include"Config.h"
#include"Threadpool.h"

void show(int i){
    std::cout << i << std::endl;
}


int main(int argc, char const *argv[])
{
    // std::string ip = "0.0.0.0";
    int port = 2222;
    Server server(port);

    std::cout << server.getPort() << std::endl;

    // server.eventListen();
    // server.mainLoop();
    
    auto a = Threadpool::get_instence(); 
    a->start();
    for(int i = 0; i < 1000; ++i)
        a->addTask(std::bind(show, i), Threadpool::L1);
    while(1){}
    std::cout << "main" << std::endl;
    return 0;
}
