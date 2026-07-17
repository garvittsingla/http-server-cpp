#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <sys/socket.h>
#include <netinet/in.h>
#include<iostream>
namespace HDE{
    class SimpleSocket {
        private:
            struct sockaddr_in address; // this is a struct that holds things socket address(IP + port) where to send or recieve data
            int sock; //(The number to handle to access your socket)
            int connection; //Status of connection wether passed or failed
        public:
            SimpleSocket(int domain,int service, int protocol,int port,u_long interface); 
            //domain -> it tell what to choose between ipv4 or ipv6
            //socket -> tell the protocol tcp(sock_stream) or udp(sock_dgram)
            //protocol -> let the system choose on service
            //port -> specifies the port 
            //interface -> interface from where to accept the connection
            // virtual: Allows derived classes to override this method with their own implementation
            // = 0: Makes this a pure virtual function, meaning:
            //      - This class becomes abstract and cannot be instantiated directly
            //      - Derived classes MUST provide an implementation of this function
            virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
            void test_connection(int item_to_test);
            struct sockaddr_in get_address();
            int get_sock();
            int get_connection();

            void set_connection(int conn);

    };
}
#endif 