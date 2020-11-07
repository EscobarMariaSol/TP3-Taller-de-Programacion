#include "server.h"

#define BUFFER_TAM 64

/******************* Métodos Privados de Server ******************************/

void Server::recvRequest(Socket& peer, std::stringbuf& request) {
    int recv = 0;
    char buffer[BUFFER_TAM] = {0};
    do {
		recv = peer.recv_msg(buffer, BUFFER_TAM);
		request.sputn(buffer, recv);
		memset(buffer, 0, BUFFER_TAM);	
	} while (recv <= 0);
}

void Server::sendResponse(Socket& peer, const Response *response) {
    std::stringbuf str_request; 
    response->serialize(str_request);
    peer.send_msg(str_request.str().c_str(), str_request.str().size());
}

/******************* Métodos Públicos de Server ******************************/

Server::Server(const char *port, Resourcer& resourcer): 
    socket(port), 
    resourcer(resourcer), 
    io_handler() {
}

Server::~Server() {
}

void Server::run() {
    Socket accept_socket;
    this->socket.accept_client(accept_socket);
    std::stringbuf request;
    recvRequest(accept_socket, request);
    HttpProtocol protocol(this->resourcer); 
    Response *response = protocol.handleRequestResponse(request.str());
    std::cout << protocol.getRequestFormat(request.str());
    sendResponse(accept_socket, response);
    accept_socket.stopComunication(SHUT_RDWR);
    delete response;
}
