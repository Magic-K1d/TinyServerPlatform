/*************************************************************************
  > File Name: Connection.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 04:56:55 PM CST
*************************************************************************/
#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory>
#include <functional>

#include "Event.h"
#include "Epoller.h"

const int BUFFER_SIZE = 1024;
 // : public std::enable_shared_from_this<Connection>
class Connection : public std::enable_shared_from_this<Connection>
{
    public:
		using Callback = std::function<void(const std::shared_ptr<Connection>&)>;
		using MessageCallback = std::function<void(const std::shared_ptr<Connection>&, char* buf, int buf_size)>;
    	

        Connection(Epoller* epoller, struct sockaddr_in addr, int fd);
        ~Connection(){};
		
		void SetMessageCB(const MessageCallback& cb) { message_cb = cb; }
        void Register();
		void HandleRead();
		void Close();

		const int GetFd() const { return m_fd; }


    private:
        int m_fd;
        struct sockaddr_in m_addr;
        std::shared_ptr<Event> conn_event;
        Epoller* m_epoller;

        Callback connection_established_cb;
        MessageCallback message_cb;
        Callback reply_complete_cb;
		Callback connection_close_cb_;


};



#endif //CONNECTION_H

