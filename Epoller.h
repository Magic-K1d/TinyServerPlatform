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
#include <memory>
#include <iostream>

#include "Event.h"
#include "Utils.h"

const int EVENT_NUM = 65535;

class Epoller{
    public:
        // typedef std::vector<Event*> Events; 
        using EventMap = std::unordered_map<int, std::shared_ptr<Event>>;

        static Epoller* GetInstance();
        ~Epoller(){ close(m_epoll_fd);};
        void AddEvent(std::shared_ptr<Event> e, bool one_shot = false, bool isET = true); 
        void DelEvent(std::shared_ptr<Event> e);
        std::vector<std::shared_ptr<Event>> Wait();
 

    private:
        static Epoller* m_epoller;
        Epoller();
        int m_epoll_fd;
        EventMap m_event_fd_map;
        std::vector<epoll_event> active_event;

};


#endif
