#include "server.h"

/******************* Métodos Privados de Server ******************************/



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
    ThreadClient *client = new ThreadClient(accept_socket, this->resourcer);
    client->start();
    client->join();
    delete client;
}
