#include "server.h"

/******************* Funciones auxiliares de Server **************************/
// Función booleana que indica si un cliente ya fue despachado y su lugar
// está libre para ser reciclado
// Pre: recibe una puntero a ThreadClient 
// Pos: devuelve true si el puntero es nulo o false en caso contrario
static bool is_dead(const ThreadClient *client) {
    return (client == nullptr);
}

/******************* Métodos Privados de Server ******************************/

void Server::addClients(std::list<ThreadClient*>& clients) {
    Socket accept_socket = this->socket.accept();
    ThreadClient *client = new ThreadClient(
    std::move(accept_socket), this->resourcer);
    clients.push_back(client);
    client->start();
}

void Server::cleanClients(std::list<ThreadClient*>& clients) {
    for (std::list<ThreadClient*>::iterator cli = clients.begin();
        cli != clients.end(); ++cli) {
        if ((*cli)->hasFinished()) {
            (*cli)->join();
            delete (*cli);
            (*cli) = nullptr;
        }
    }
    clients.remove_if(is_dead);
}

void Server::stopAndCleanClients(std::list<ThreadClient*>& clients) {
    for (std::list<ThreadClient*>::iterator client = clients.begin();
        client != clients.end(); ++client) {
        (*client)->stop();
        (*client)->join();
        delete (*client);
    }
}

/******************* Métodos Públicos de Server ******************************/

Server::Server(const char *port, Resourcer& resourcer): 
    socket(port), 
    resourcer(resourcer),
    keep_running(true) {
}

Server::~Server() {
}

void Server::run() {
    std::list<ThreadClient*> clients;
    while (this->keep_running) {   
        try {
            addClients(clients);
            cleanClients(clients);
        } catch(const std::exception& e) {
            stopAndCleanClients(clients);
            std::string error = e.what();
            if ((error == "Server cannot accept client." ) 
                && !this->keep_running) break;
            syslog(LOG_CRIT, "Error: %s", e.what());
        } catch (...) {
            syslog(LOG_CRIT, "Unknown Error\n");
        }
    }
}

void Server::stop() {
    this->keep_running = false;
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}
