#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include "thread.h"
#include "../common_src/socket.h"
#include "protocol.h"
#include "resourcer.h"
#include "../common_src/response.h"
#include <atomic>

// Clase correspondiente al thread que despacha un cliente, hereda de Thread.
// Cuenta con los siguientes atributos:
// peer, que corresponde al socket a través del cual establecera 
// comunicación con el cliente
// resourcer, corresponde al repositorio en el cual están almacenados los 
// recursos que serán accedidos/ modificados segun los petitorios de clientes.
// running, corresponde a un booleano, que indica si el thread aún sigue 
// ejecutandose o ya terminó
class ThreadClient: public Thread {
private:
    Socket peer;
    Resourcer resourcer;
    std::atomic<bool> running;
    // Método que recibe el petitorio del cliente y loguarda dentro del 
    // buffer "request"
    // Pre: el petitorio del cliente se ha almacenado en el buffer "request"
    void recvRequest(std::stringbuf& request);
    // Método que envía una respuesta al cliente
    // Pre: el cliente ha enviado un petitorio previamente y el mismo ha
    // sido procesado
    // Pos: la respuesta al petitorio del cliente se ha enviado
    void sendResponse(const Response *response);

public:
    // Constructor
    ThreadClient(Socket& peer, Resourcer& resourcer);
    // Destructor
    ~ThreadClient();
    // Método que se hereda de Thread, es a través del cual se lanzará la 
    // ejecución del nuevo thread
    void run() override;
    // Método que se hereda de thread, el cual se emplea para indicarle 
    // al thread que debe detener su ejecución ordenadamente
    void stop() override;
};

#endif // THREAD_CLIENT_H
