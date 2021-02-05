#ifndef CLIENT
#define CLIENT

#include <string>
#include "Utils.h"

const int MAX_EVENT_NUMBER = 5; //最大事件数

class Client
{
public:
	Client(std::string name);
	~Client();

	int init();
	void mainLoop();
	void sendMessage();

private:

	std::string m_name;
	int m_sockfd;
    epoll_event m_events[ MAX_EVENT_NUMBER ];
    int m_epoll_fd;
	int m_pipefd[2];

};

#endif