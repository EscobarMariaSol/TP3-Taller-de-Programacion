#include "server.h"

/******************* Funciones auxiliares de Server ******************************/

static bool is_dead(const ThreadClient *client) {
    return (client == nullptr);
}

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
    std::list<ThreadClient*> clients;
    while (this->keep_running) {   
        try {
            Socket accept_socket = this->socket.accept();
            ThreadClient *client = new ThreadClient(
                std::move(accept_socket), std::ref(this->resourcer));
            clients.push_back(client);
            client->start();
            for (std::list<ThreadClient*>::iterator client = clients.begin();
                client != clients.end(); ++client) {
                if ((*client)->hasFinished()) {
                    (*client)->join();
                    delete (*client);
                    (*client) = nullptr;
                }
            }
            clients.remove_if(is_dead);
        } catch(const std::runtime_error& e) {
            std::string error = e.what();
            if (error == "Server cannot accept client." ) break;
        }
    }
}

void Server::stop() {
    this->keep_running = false;
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}