/*************************************************************************
  > File Name: Epoller.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 10:40:35 PM CST
*************************************************************************/

#include"Epoller.h"

Epoller* Epoller:: m_epoller = new Epoller();

Epoller::Epoller() : m_event_fd_map(){
    m_epoll_fd = epoll_create1(EPOLL_CLOEXEC);
}

Epoller* Epoller::getInstance(){ return m_epoller;}

void Epoller::addEvent(Event* e, bool one_shot, bool isET)
{
    epoll_event event;
    event.data.fd = e->getFD();
    if(e->getEventType() == Event::READ)
        event.events = EPOLLIN | EPOLLRDHUP | EPOLLPRI;
    else if(e->getEventType() == Event::WRITE)
        event.events = EPOLLOUT | EPOLLRDHUP;
    if (isET)
        event.events |= EPOLLET;
    if (one_shot)
        event.events |= EPOLLONESHOT;
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, e->getFD(), &event);
    Utils::setnonblocking(e->getFD());
    m_event_fd_map[e->getFD()] = e;
}

std::vector<Event*> Epoller::wait(){
    std::vector<Event*> r_events;
    std::vector<epoll_event> active_event;
    int number = epoll_wait( m_epoll_fd, &*active_event.begin(), active_event.size(), -1);
    if (number < 0 && errno != EINTR){
        // TODO :: LOG ERROR
        // std::cout << "epoll failure" << std::endl;
    }
    
    for(int i = 0; i < number; ++i){
        auto e = m_event_fd_map[active_event[i].data.fd];
        r_events.push_back(e);
    }
    return r_events;   
}


