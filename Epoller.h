/*************************************************************************
  > File Name: Epoller.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Feb 2021 10:38:30 PM CST
*************************************************************************/
#ifndef EPOLLER_H
#define EPOLLER_H


#include<sys/epoll.h>

class Epoller{
    public:
        Epoller();
        ~Epoller();

    private:
        int m_epoll_fd;

};


#endif
