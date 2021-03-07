#ifndef SERVER
#define SERVER

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>
#include <string>
#include <string.h>
#include <iostream>

#include "Utils.h"
#include "Epoller.h"
#include "Event.h"

const int MAX_FD = 65536;           //最大文件描述符
// const int MAX_EVENT_NUMBER = 10000; //最大事件数
const int BUFFER_SIZE = 64;

class Server
{
    public:
        Server(int port);
        ~Server();
        void init(){};
        void eventListen();
        void mainLoop();
        int getPort();


    private:
        int m_listenfd;
        int m_OPT_LINGER = 0;
        // int m_epoll_fd;
        Epoller* m_epoller;
        int m_port;
        // epoll_event m_events[MAX_EVENT_NUMBER];
        Event* listen_event;

};





#endif
