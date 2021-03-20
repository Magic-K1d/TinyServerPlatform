/*************************************************************************
  > File Name: Epoller.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 10:40:35 PM CST
*************************************************************************/

#include"Epoller.h"

Epoller* Epoller:: m_epoller = new Epoller();

Epoller::Epoller() : 
    m_event_fd_map(), 
    active_event(EVENT_NUM)
{
    m_epoll_fd = epoll_create1(EPOLL_CLOEXEC);
}

Epoller* Epoller::GetInstance(){ return m_epoller;}

void Epoller::AddEvent(std::shared_ptr<Event> e, bool one_shot, bool isET)
{
    // std::cout << "AddEvent" << std::endl;
    epoll_event event;
    event.data.fd = e->GetFD();
    if(e->GetEventType() == Event::READ){
        // std::cout << "ReadEvent" << std::endl;
        event.events = EPOLLIN | EPOLLRDHUP | EPOLLPRI;
    }
    else if(e->GetEventType() == Event::WRITE)
        event.events = EPOLLOUT | EPOLLRDHUP;
    if (isET)
        event.events |= EPOLLET;
    if (one_shot)
        event.events |= EPOLLONESHOT;
    if(epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, e->GetFD(), &event) < 0) 
        // std::cout << "epoll_ctl failure!" << std::endl;
    Utils::setnonblocking(e->GetFD());
    m_event_fd_map[e->GetFD()] = e;
}

std::vector<std::shared_ptr<Event>> Epoller::Wait(){
    std::vector<std::shared_ptr<Event>> r_events;
        int number = epoll_wait( m_epoll_fd, &*active_event.begin(), active_event.size(), -1);
    if (number < 0 && errno != EINTR){
        // TODO :: LOG ERROR
        std::cout << "epoll failure" << std::endl;
    }
    
    for(int i = 0; i < number; ++i){
        // std::cout << "Epoll find a Event!" << std::endl;
        auto e = m_event_fd_map[active_event[i].data.fd];
        r_events.push_back(e);
    }
    return r_events;   
}


