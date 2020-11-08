#define _POSIX_C_SOURCE 201112L
#include "socket.h"
#include <iostream>

/******************* Métodos Privados de ServerSocket ************************/

void Socket::activeReuseAddress() {
	int val = 1;
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0)
        throw std::runtime_error("Active reuse adrress cannot be set.");
}

void  Socket::setFileDescriptor(const HandlerAddrinfo& addr) {
	this->fd = addr.openSocket();
}

void Socket::bindAndListen(HandlerAddrinfo& addr) {
	addr.bindAddress(this->fd);
	if (listen(this->fd, 10) < 0) 
        throw std::runtime_error("Listen failed.");
}

/******************* Métodos Públicos de Socket (peer) ***********************/

Socket::Socket() {
}

void Socket::close() {
	if (this->fd != -1) ::close(this->fd);
}

void Socket::shutdown(int channel) {
	::shutdown(this->fd, channel);
}

/***************************** Servidor **************************************/

Socket::Socket(const char *port) {
    HandlerAddrinfo addrinfo(NULL, port, AI_PASSIVE);
	addrinfo.callGetAddrinfo(NULL, port);
	setFileDescriptor(addrinfo);
    activeReuseAddress();
    bindAndListen(addrinfo);
}

void Socket::accept(Socket& accept_socket) {
    int fd = ::accept(this->fd, NULL, NULL);
	if (fd == -1) 
        throw std::runtime_error("Server cannot accept client.");
    accept_socket.fd = fd;
}

/***************************** Cliente ***************************************/

Socket::Socket(const char* host, const char* port) {
    HandlerAddrinfo addrinfo(host, port, 0);
	addrinfo.callGetAddrinfo(host, port);
    addrinfo.connectAddress(this->fd);
}

/*************************** Métodos compartidos *****************************/

Socket::Socket(Socket& other) {
	this->fd = std::ref(other.fd);
}

Socket& Socket::operator=(Socket& other) {
	this->fd = std::ref(other.fd);
	return *this;
}


int Socket::send(const char *buffer, size_t size) {
	size_t total = 0, sent = 0;
	do {
		sent = ::send(this->fd, &buffer[total], size-total, MSG_NOSIGNAL);
		if (sent > 0)  total += sent;
	} while ((sent >= 0) && (total < size));
	if (sent < 0) throw std::runtime_error("Sent message fail.");
	return total;
}

int Socket::recv(char *buffer, const size_t size) {
	size_t total = 0, received = 0;
	do {
		received = ::recv(this->fd, (buffer + total), (size-total), 0);
		if (received > 0) total += received;
	} while (received == (size - total));
    if (received < 0) throw std::runtime_error("Receive message fail.");
	return total;
}

Socket::~Socket() {
    if (this->fd != -1) {
		::close(this->fd);
	}
}
