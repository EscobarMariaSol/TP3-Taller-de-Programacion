#define _POSIX_C_SOURCE 201112L
#include "socket.h"


/******************* Métodos Públicos de Socket ******************************/

Socket::Socket() {
}

Socket::~Socket() {
    if (this->fd) {
		shutdown(this->fd, SHUT_RDWR); // devuelve 0 si ok, sino -1
    close(this->fd);
	}
}

void Socket::setFileDescriptor(const int fd) {
	if (fd == -1) throw std::runtime_error("File descriptor in not valid");
	this->fd = fd;
}

int Socket::send_msg(const unsigned char *buffer, size_t size) {
	size_t total = 0, sent = 0;
	do {
		sent = send(this->fd, &buffer[total], size-total, MSG_NOSIGNAL);
		if (sent > 0)  total += sent;
	} while ((sent > 0) && (total < size));
	if (sent <= 0)  return -1;
	return total;
}

int Socket::recv_msg(unsigned char *buffer, const size_t size) {
	size_t total = 0, recived = 0;
	do {
		recived = recv(this->fd, (buffer + total), (size-total), 0);
		if (recived > 0) total += recived;
	} while (recived == (size - total));
    if (recived < 0) return -1;
	return total;
}
