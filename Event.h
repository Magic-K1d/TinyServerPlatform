/*************************************************************************
  > File Name: Event.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Wed 03 Feb 2021 05:14:21 PM CST
*************************************************************************/
#ifndef EVENT_H
#define EVENT_H

// #include<sys/epoll.h>
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

        Event(int fd, EVENT_TYPE event_type);
        ~Event(){};

        void HandleEvent();
        
        // void EnableReadEvents() { m_events |= (EPOLLIN | EPOLLPRI); }
        // void EnableWriteEvents() { m_events |= EPOLLOUT; }
        void SetCallBack(Callback&& cb);

        const int GetFD() const{ return m_fd;}
        // int getEvents() const{ return m_events;}
        EVENT_TYPE GetEventType(){ return m_event_type;}

    private:
        const int m_fd;
        // int m_events;
        EVENT_TYPE m_event_type;
        Callback m_read_callback;
        Callback m_write_callback;
        Callback m_error_callback;
        Callback m_close_callback;

};


#endif
