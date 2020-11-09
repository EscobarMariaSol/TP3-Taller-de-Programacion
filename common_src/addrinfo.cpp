#include "addrinfo.h"

/******************* Métodos Privados de HandlerAddrinfo *********************/

void HandlerAddrinfo::init(const int flag) {
    struct addrinfo *_hints = &this->hints;
    memset(_hints, 0, sizeof(struct addrinfo));
	_hints->ai_family = AF_INET;       
	_hints->ai_socktype = SOCK_STREAM; 
	_hints->ai_flags = flag;
	_hints->ai_protocol = 0; 
}


/******************* Métodos Públicos de HandlerAddrinfo *********************/

HandlerAddrinfo::HandlerAddrinfo(const int flag): 
    hints(), addr() {
    init(flag);
}

HandlerAddrinfo::~HandlerAddrinfo() {
    if (this->addr) 
        freeaddrinfo(this->addr);
}

void HandlerAddrinfo::callGetAddrinfo(const char* host, const char* port) {
    if (getaddrinfo(host, port, &this->hints, &this->addr) < 0)
        throw std::runtime_error("Socket address cannot be set.");
}

void HandlerAddrinfo::bindAddress(const int fd) {
    struct addrinfo *aux_addr; 
	for (aux_addr = addr; aux_addr; aux_addr = aux_addr->ai_next)
		if (bind(fd, aux_addr->ai_addr, aux_addr->ai_addrlen) > -1) break;
	if (!aux_addr) 
        throw std::runtime_error("Bind address failed.");
}

void HandlerAddrinfo::connectAddress(int& fd) {
    struct addrinfo *aux;
	for (aux = this->addr; aux; aux = aux->ai_next) {
		fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
		if (fd == -1) continue;
		if (connect(fd, aux->ai_addr, aux->ai_addrlen) > -1) break;
		else 
			close(fd);
	}
	if (!aux) throw std::runtime_error("Conection to server failed.");
}

int HandlerAddrinfo::openSocket() const {
	int skt_fd;
	skt_fd = socket(
		this->addr->ai_family, 
		this->addr->ai_socktype, 
		this->addr->ai_protocol);
	if (skt_fd == -1) 
        throw std::runtime_error("Socket file descriptor cannot be set.");
	return skt_fd;
}
