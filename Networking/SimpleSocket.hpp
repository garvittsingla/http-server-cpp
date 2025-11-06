#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace HDE{
    class SimpleSocket {
        private:
            struct sockaddr_in address;
            int sock;
            int connection;
        public:
            SimpleSocket(int domain,int service int protocol,int port,u_long interface); 
            virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
    };
}
#endif 