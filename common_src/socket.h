#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <atomic>
#include <string>


// Clase correspondiente a un socket
// La clase cuenta con un único atributo correspondiente a su file descriptor.
class Socket {
private:
    std::atomic<int> fd;
    
public:
    Socket(struct addrinfo **addr, const char* host);
    ~Socket();
    int accept(Socket& accept_socket);
    int send(const std::string message, const size_t size);
    int receive(std::string& buffer, const size_t size);
};

#endif // COMMON_SOCKET_H
