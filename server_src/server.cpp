#include "server.h"

/******************* Métodos Públicos de Server ******************************/

Server::Server(const char *port, Resourcer& resourcer): 
    socket(port), 
    resourcer(resourcer), 
    io_handler(),
    keep_running(true) {
}

Server::~Server() {
}

void Server::run() {
    while (this->keep_running) {   
        Socket accept_socket;
        this->socket.accept_client(accept_socket);
        ThreadClient *client = new ThreadClient(accept_socket, this->resourcer);
        client->start();
        client->join();
        delete client;
    }
}

void Server::stop() {
    this->keep_running = false;
    this->socket.stopComunication(SHUT_RDWR);
}