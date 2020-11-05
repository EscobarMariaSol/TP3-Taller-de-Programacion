#define _POSIX_C_SOURCE 201112L
#include "socket.h"


/******************* Funciones Auxiliares de Socket **************************/
// Inicializa un struct addrinfo indicando que se utilizara el canal de 
// counicación TCP y la familia IPV4
// Pre: recibe un puntero a un struct addrinfo y un flag
// Pos: el struct addrinfo se ha inicializado
static void initAddrinfo(struct addrinfo* hints, const int flag) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;       
	hints->ai_socktype = SOCK_STREAM; 
	hints->ai_flags = flag;
	hints->ai_protocol = 0; 
}
/******************* Métodos Privados de Socket ******************************/
void callGetAddrInfo(struct addrinfo **addr, const char* host, 
    const char* port, int flag) {
	struct addrinfo hints;
	struct addrinfo *address;
	initAddrinfo(&hints, flag); // agregar excepciones
	getaddrinfo(host, port, &hints, &address); // agregar excepciones
	*addr = address;
}

/******************* Métodos Públicos de Socket ******************************/

Socket::Socket(const std::string host, const std::string port) {
}

Socket::~Socket() {
    shutdown(this->fd, SHUT_RDWR); // devuelve 0 si ok, sino -1
    close(this->fd);
}
