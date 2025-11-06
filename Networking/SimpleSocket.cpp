#include <SimpleSocket.hpp>

HDE::SimpleSocket::SimpleSocket(int domain,int service,int protocol,int port,u_long interface){
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    sock = socket(domain, service, protocol);
    connection = connect_to_network();
}