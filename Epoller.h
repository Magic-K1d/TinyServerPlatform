/*************************************************************************
  > File Name: Epoller.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 10:38:30 PM CST
*************************************************************************/
#ifndef EPOLLER_H
#define EPOLLER_H


#include <sys/epoll.h>
#include <vector>
#include <unordered_map>
#include "Event.h"
#include "Utils.h"

class Epoller{
    public:
        // typedef std::vector<Event*> Events; 
        typedef std::unordered_map<int, Event*> EventMap;

        static Epoller* getInstance();
        ~Epoller(){ close(m_epoll_fd);};
        void addEvent(Event* e, bool one_shot, bool isET); 
        std::vector<Event*> wait();
 

    private:
        static Epoller* m_epoller;
        Epoller();
        int m_epoll_fd;
        EventMap m_event_fd_map;
        
};


#endif
