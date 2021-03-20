#include <iostream>
#include "Client.h"

void addfd(int epollfd, int fd, bool one_shot, bool isET)
{
    epoll_event event;
    event.data.fd = fd;

    if (isET)
        event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    else
        event.events = EPOLLIN | EPOLLRDHUP;

    if (one_shot)
        event.events |= EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    Utils::setnonblocking(fd);
}



Client::Client(std::string name):m_name(name){
    std::cout << "My name is :" << name << std::endl;
};

Client::~Client(){
    close( m_sockfd );
    close( m_epoll_fd );
    close( m_pipefd[1] );
    close( m_pipefd[0] );
};

int Client::init(){
    int ret = 0;

    ret = pipe( m_pipefd );
    assert( ret != -1 );

    const char* str1 = "hello !!! im MK!";

    char* ip = "60.205.210.237";
    int port = 2222;
    struct sockaddr_in address;
    bzero( &address, sizeof address);
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    m_sockfd = socket( PF_INET, SOCK_STREAM, 0);
    assert( m_sockfd >= 0 );

    if ( connect( m_sockfd, ( struct sockaddr* )&address, sizeof( address ) ) < 0 )
    {
        std::cout << "connection failed" << std::endl;
        close( m_sockfd );
        return 1;
    }

    std::cout << "connection success" << std::endl;
    m_epoll_fd = epoll_create(MAX_EVENT_NUMBER);
    assert( m_epoll_fd != -1 );

    addfd(m_epoll_fd, m_sockfd, false, false);
    addfd(m_epoll_fd, 0, false, false);

    ret = send(m_sockfd, m_name.c_str(), sizeof m_name.c_str(), 0);
    std::cout << "send mss" << std::endl;
    assert( ret != -1 );
    return 0;
}


int main(int argc, char const *argv[])
{
    std::string name;
    std::cout << "Set your name:";
    std::cin >> name;
    Client client(name);
    client.init();
    return 0;
}
