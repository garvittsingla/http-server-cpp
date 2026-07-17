#ifndef BindingSocket_hpp
#define BindingSocket_hpp


#include "SimpleSocket.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
namespace HDE {
    class BindingSocket: public SimpleSocket
    {
        public:
            BindingSocket(int domain,int service,int protocol,int port,u_long interface);
            int connect_to_network(int sock,struct sockaddr_in address);

    };
}

#endif