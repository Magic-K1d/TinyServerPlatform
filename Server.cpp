#include "Server.h"
#include <iostream>


Server::~Server(){
	close( m_listenfd );
	close( m_epoll_fd );
}

void Server::eventListen(){

    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);

    //优雅关闭连接
    if (0 == m_OPT_LINGER)
    {
        struct linger tmp = {0, 1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }
    else if (1 == m_OPT_LINGER)
    {
        struct linger tmp = {1, 1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }

    struct sockaddr_in address;
	// memset( &address, 0, sizeof address);
	bzero(&address, sizeof address);
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons( m_port );

	int ret = bind( m_listenfd, ( struct sockaddr*) &address, sizeof address);
	assert( ret != -1);
	
	ret = listen( m_listenfd, 5);
	assert( ret != -1);
	
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );

    m_epoll_fd = epoll_create(5);
    assert(m_epoll_fd != -1);

    Utils::addfd(m_epoll_fd, m_listenfd, false, true);


}

void Server::mainLoop(){
    bool stop_server = false;
	char buf[ BUFFER_SIZE ];
    while (!stop_server)
    {
        int number = epoll_wait(m_epoll_fd, m_events, MAX_EVENT_NUMBER, -1);

        if (number < 0 && errno != EINTR)
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }

		for (int i = 0; i < number; i++)
		{
            int sockfd = m_events[i].data.fd;

            //处理新到的客户连接
            if (sockfd == m_listenfd)
            {
			    struct sockaddr_in client_address;
			    socklen_t client_addrlength = sizeof( client_address );
            	int connfd= accept( m_listenfd, ( struct sockaddr*) &client_address, &client_addrlength);
	            assert( connfd != -1);
	            Utils::addfd(m_epoll_fd, connfd, false, true);
	            std::cout << "get connected from fd:" << connfd <<  std::endl;
            }
            else if(m_events[i].events & EPOLLIN){
	            int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
	            if(ret <= 0){
	            	std::cout << "nodata" << std::endl;
	            	break;
	            }
	            else 
	            	std::cout << "get " << ret << " data : " << buf << " from " << sockfd << std::endl;
	            	if (buf == "stop")
	            	{
	            		stop_server = true;
	            	}
            }
        }
    }

}

int Server::getPort(){
	return this->m_port;
}


int main(int argc, char const *argv[])
{
	// std::string ip = "0.0.0.0";
	int port = 2222;
	Server server(port);

	std::cout << server.getPort() << std::endl;

	server.eventListen();
	server.mainLoop();
	return 0;
}
