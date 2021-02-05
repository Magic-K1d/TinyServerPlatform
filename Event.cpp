/*************************************************************************
  > File Name: Event.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 03:46:01 PM CST
*************************************************************************/

#include "Event.h"

void Event::HendleEvent(EVENT_TYPE type){
    if( type == CLOSE) {
        if( m_close_callback) m_close_callback();
    }
    else if( type == ERROR){
        if(m_error_callback) m_error_callback();
        if(m_close_callback) m_close_callback();
    }
    else if( type == READ){
        if(m_read_callback) m_read_callback();
    } 
    else if( type == WRITE){
        if(m_write_callback) m_write_callback();
    }
}
