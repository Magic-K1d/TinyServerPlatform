/*************************************************************************
  > File Name: main.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 06:24:57 PM CST
 *************************************************************************/

#include"Config.h"
#include"Threadpool.h"
#include<chrono>

void show(int i){
    std::cout << std::this_thread::get_id() << ":";
    std::cout << i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    
}

void show1(int i){
    std::cout << std::this_thread::get_id() << ":";
    std::cout << i+100000 << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    
}


void thread_pool_test(){
    auto a = Threadpool::get_instence(); 
    a->start();
    // std::this_thread::sleep_for(std::chrono::seconds(3));    
    for(int i = 0; i < 1000; ++i)
        a->addTask(std::bind(show, i), Threadpool::L3);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for(int i = 0; i < 10; ++i)
        a->addTask(std::bind(show1, i), Threadpool::L1);
    std::this_thread::sleep_for(std::chrono::seconds(10));    

    delete a;
    // while(1){}
}


void server_test(){
    // std::string ip = "0.0.0.0";
    int port = 2222;
    Server server(port);

    std::cout << server.getPort() << std::endl;

    server.eventListen();
    server.mainLoop();
}
 

int main(int argc, char const *argv[])
{
    thread_pool_test();
   std::cout << "main" << std::endl;
    return 0;
}
