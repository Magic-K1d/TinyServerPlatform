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

#include "Utils.h"

const int MAX_FD = 65536;           //最大文件描述符
const int MAX_EVENT_NUMBER = 10000; //最大事件数
const int BUFFER_SIZE = 64;

class Server
{
public:
	Server(int port):m_port(port){};
	~Server();
	void init(){};
	void eventListen();
	void mainLoop();
	int getPort();
	void addfd(int epoll_fd, int new_fd, bool one_shot = false);
	int setnonblocking(int fd);


private:
	int m_listenfd;
	int m_OPT_LINGER = 0;
	int m_epoll_fd;
	int m_port;
	epoll_event m_events[MAX_EVENT_NUMBER];

};





#endif
