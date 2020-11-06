#include "server.h"

/******************* Métodos Públicos de Server ******************************/

void Server::saveRoot(const char *path) {
    
}

/******************* Métodos Públicos de Server ******************************/

Server::Server(): resourcer() {
}

Server::~Server() {
}

void Server::run(const char *port, const char *path) {
    saveRoot(path);
}