#include "client_socket.h"

/******************* Métodos Públicos de ClientSocket ************************/

ClientSocket::ClientSocket(const char* host, const char* port): Socket() {
    HandlerAddrinfo addrinfo(host, port, 0);
	addrinfo.callGetAddrinfo(host, port);
    addrinfo.connectAddress(this->fd);
}

ClientSocket::~ClientSocket() {
}

