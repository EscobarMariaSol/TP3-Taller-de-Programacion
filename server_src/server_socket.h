#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "socket.h"
#include "addrinfo.h"

class ServerSocket: public Socket {
private:
    void setFileDescriptor(const Addrinfo& addrinfo);
    void bindAndListen(Addrinfo& addrinfo);
    void activeReuseAddress();

public:
    ServerSocket(const char *port);
    ~ServerSocket();
    // Crea el socket aceptador en representación de la conexión establecida
    // Pre: Recibe una referencia a un nuevo socket
    // que funcionará como canal de comunicación
    void accept_client(Socket& accept_socket);
};

#endif // SERVER_SOCKET_H
