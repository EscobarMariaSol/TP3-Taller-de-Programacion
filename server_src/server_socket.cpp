#include "server_socket.h"

/******************* Métodos Privados de ServerSocket ************************/

// Activa la opcion de reusar la direccion en caso de que esta
// no este disponible por un TIME_WAIT
// Pos: se activa la opción de reusar la dirección, si ocurre un error lanza 
// una excepción informando de lo ocurrido.
void ServerSocket::activeReuseAddress() {
	int val = 1;
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0);
        throw std::runtime_error("Active reuse adrress cannot be set.");
}

// Asigna el file descriptor al socket que se le pasa por parámetro
// utilizando la información de la dirección addrs
// Pos: se ha asignado un file descriptor al socket, si ocurre un error 
// durante el proceso de asignación se lanza una excepción informando 
// lo ocurrido
void  ServerSocket::setFileDescriptor(const HandlerAddrinfo& addr) {
	this->fd = addr.openSocket();
}

// Establece que el servidor está listo para escuchar conexiones
// y la cantidad de conexiones en espera que se habilitarán
// Pos: 
void ServerSocket::bindAndListen(HandlerAddrinfo& addr) {
	addr.bindAddress(this->fd);
	if (listen(this->fd, 1) < 0) 
        throw std::runtime_error("Listen failed.");
}

/******************* Métodos Públicos de ServerSocket ************************/


ServerSocket::ServerSocket(const char *port): Socket() {
    HandlerAddrinfo addrinfo(NULL, port, AI_PASSIVE);
	addrinfo.callGetAddrinfo(NULL, port);
	setFileDescriptor(addrinfo);
    activeReuseAddress();
    bindAndListen(addrinfo);
}

ServerSocket::~ServerSocket() {
}

void ServerSocket::accept_client(Socket& accept_socket) {
    int fd = accept(this->fd, NULL, NULL);
	if (fd == -1) 
        throw std::runtime_error("Server cannot accept client.");
    accept_socket.setFileDescriptor(fd);
}