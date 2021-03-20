#ifndef SERVER
#define SERVER

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>

#include "Utils.h"
#include "Epoller.h"
#include "Threadpool.h"
#include "Event.h"
#include "Connection.h"

const int MAX_FD = 65536;           //最大文件描述符
// const int MAX_EVENT_NUMBER = 10000; //最大事件数

class Server
{
    public:
        Server(int port);
        ~Server();
        void Init(){};
        void EventListen();
        void MainLoop();
        void HandleNewConnection();
        void SetMessageCB(Connection::MessageCallback&& cb) { m_message_cb = cb; }

        const int GetPort() const { return m_port; };


    private:
        int m_listenfd;
        int m_OPT_LINGER = 0;
        // int m_epoll_fd;
        Epoller* m_epoller;
        Threadpool* m_threadpool;
        int m_port;
        // epoll_event m_events[MAX_EVENT_NUMBER];
        std::shared_ptr<Event> listen_event;
        Connection::MessageCallback m_message_cb;

};





#endif
