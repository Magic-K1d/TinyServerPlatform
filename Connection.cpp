/*************************************************************************
  > File Name: Connection.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 04:56:20 PM CST
*************************************************************************/

#include"Connection.h"




Connection::Connection(Epoller* epoller, struct sockaddr_in addr, int fd) : 
	m_addr(addr), 
	m_fd(fd),
	conn_event(new Event(fd, Event::READ)),
    m_epoller(epoller)
{
}

void Connection::HandleRead(){
	
	char buf[ BUFFER_SIZE ];
	int ret = recv( m_fd, buf, BUFFER_SIZE-1, 0 );

	if (ret >= 0)
	{
		if (message_cb)
		{
			message_cb(shared_from_this(), buf, ret);
            // shared_from_this()
		}
	}
}

void Connection::Register(){
	conn_event->SetCallBack(std::bind(&Connection::HandleRead , shared_from_this()));
    m_epoller->AddEvent(conn_event);
}
