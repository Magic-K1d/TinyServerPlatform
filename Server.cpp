#include "Server.h"

Server::Server(int port):m_port(port){
    m_epoller = Epoller::GetInstance();
    m_threadpool = Threadpool::GetInstance();
};

Server::~Server(){
    close( m_listenfd );
    // close( m_epoll_fd );
}

void Server::EventListen(){

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

    // struct sockaddr_in client_address;
    // socklen_t client_addrlength = sizeof( client_address );

    // m_epoll_fd = epoll_create(5);
    // assert(m_epoll_fd != -1);
    listen_event = std::make_shared<Event>(m_listenfd, Event::READ);
    listen_event->SetCallBack(std::bind(&Server::HandleNewConnection, this));
    m_epoller->AddEvent(listen_event);
    
    // Utils::addfd(m_epoll_fd, m_listenfd, false, true);


}

void Server::HandleNewConnection(){
    std::cout << "NewConnection" << std::endl;
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );
    int connfd = accept4(m_listenfd, (struct sockaddr*)&client_address, &client_addrlength, SOCK_NONBLOCK | SOCK_CLOEXEC);
    assert( connfd != -1);   
    std::shared_ptr<Connection> new_connection( new Connection(m_epoller, client_address, connfd));
    new_connection->SetMessageCB(m_message_cb);
    // m_epoller->AddEvent(new_connection->conn_event);
    new_connection->Register();
}


void Server::MainLoop(){
    bool stop_server = false;
    m_threadpool->Start();
    while(!stop_server){
        auto events = m_epoller->Wait();
        for(auto& e : events){
            std::cout << "Event!!" << std::endl;
            m_threadpool->AddTask(std::bind(&Event::HandleEvent, e));
        }
    }






    // while (!stop_server)
    // {
    //     int number = epoll_wait(m_epoll_fd, m_events, MAX_EVENT_NUMBER, -1);

    //     if (number < 0 && errno != EINTR)
    //     {
    //         std::cout << "epoll failure" << std::endl;
    //         break;
    //     }

    //     for (int i = 0; i < number; i++)
    //     {
    //         int sockfd = m_events[i].data.fd;

    //         //处理新到的客户连接
    //         if (sockfd == m_listenfd)
    //         {
    //             struct sockaddr_in client_address;
    //             socklen_t client_addrlength = sizeof( client_address );
    //             int connfd= accept( m_listenfd, ( struct sockaddr*) &client_address, &client_addrlength);
    //             assert( connfd != -1);
    //             Utils::addfd(m_epoll_fd, connfd, false, true);
    //             std::cout << "get connected from fd:" << connfd <<  std::endl;
    //         }
    //         else if(m_events[i].events & EPOLLIN){
    //             int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
    //             if(ret <= 0){
    //                 std::cout << "nodata" << std::endl;
    //                 break;
    //             }
    //             else 
    //                 std::cout << "get " << ret << " data : " << buf << " from " << sockfd << std::endl;
    //             if (buf == "stop")
    //             {
    //                 stop_server = true;
    //             }
    //         }
    //     }
    // }

}


