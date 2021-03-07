/*************************************************************************
  > File Name: Event.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 03:46:01 PM CST
 *************************************************************************/

#include "Event.h"


Event::Event(int fd, EVENT_TYPE event_type):
m_fd(fd), 
m_events(EPOLLRDHUP), 
m_event_type(event_type)
{
    if( event_type == READ){
        EnableReadEvents();
    } 
    else if( event_type == WRITE){
        EnableWriteEvents();
    }
}

void Event::HandleEvent(){
    if( m_event_type == CLOSE) {
        if( m_close_callback) m_close_callback();
    }
    else if( m_event_type == ERROR){
        if(m_error_callback) m_error_callback();
        if(m_close_callback) m_close_callback();
    }
    else if( m_event_type == READ){
        if(m_read_callback) m_read_callback();
    } 
    else if( m_event_type == WRITE){
        if(m_write_callback) m_write_callback();
    }
}

void Event::SetCallBack(Callback& cb){
    if( m_event_type == CLOSE) {
        m_close_callback = cb;
    }
    else if( m_event_type == ERROR){
        m_error_callback = cb;
    }
    else if( m_event_type == READ){
        m_read_callback = cb;
    } 
    else if( m_event_type == WRITE){
        m_write_callback = cb;
    }
}
