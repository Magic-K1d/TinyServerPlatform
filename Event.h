/*************************************************************************
  > File Name: Event.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Wed 03 Feb 2021 05:14:21 PM CST
*************************************************************************/
#ifndef EVENT_H
#define EVENT_H

#include<sys/epoll.h>
#include<functional>


class Event{
    public:    
        using Callback = std::function<void()>;
        enum EVENT_TYPE
        {
            READ = 0,
            WRITE,
            CLOSE,
            ERROR
        };        


        Event(int fd):m_fd(fd), m_events(EPOLLRDHUP) {};
        ~Event(){};

        void HandleEvent();
        
        void EnableReadEvents() { m_events |= (EPOLLIN | EPOLLPRI); }
        void EnableWriteEvents() { m_events |= EPOLLOUT; }
        void SetCallBack(Callback& cb,EVENT_TYPE type);

        void HendleEvent(EVENT_TYPE type);


        int GetFD() const{ return m_fd;}
        int GetEvents() const{ return m_events;}


    private:
        const int m_fd;
        int m_events;
        Callback m_read_callback;       
        Callback m_write_callback;       
        Callback m_error_callback;       
        Callback m_close_callback;       

};


#endif
