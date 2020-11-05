#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "socket.h"
#include "addrinfo.h"

class ClientSocket: public Socket {
public:
    ClientSocket(const char* host, const char* port);
    ~ClientSocket();
};

#endif // CLIENT_SOCKET_H
