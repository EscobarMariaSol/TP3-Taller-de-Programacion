#ifndef SERVER_H
#define SERVER_H

#include "../common_src/socket.h"
#include "../common_src/response.h"
#include "../common_src/io_handler.h"
#include "thread.h"
#include "thread_client.h"
#include "protocol.h"
#include "resourcer.h"
#include <thread>
#include <functional>
#include <list>
#include <string>
#include <utility>

// Clase correspondiente al thread servidor, que se encarga de aceptar
// nuevos cliente y despacharlos
// Cuenta con los siguientes atributos:
// socket, correspondiente al socket desde el cual el servidor 
// escuchará a nuevos clientes
// resourcer, corresponde al repositorio en el cual están almacenados los 
// recursos que serán accedidos/ modificados segun los petitorios de clientes.
// io_handler, será el encargado de mostrar por pantalla los petitorios de los
// diferentes clientes
class Server: public Thread {
private:
    Socket socket;
    Resourcer resourcer;
    IOHandler io_handler;
    std::atomic<bool> keep_running;

public:
    // Constructor
    Server(const char *port, Resourcer& resourcer);
    // Destructor
    ~Server();
    // Método que se hereda de Thread, es a través del cual se lanzará la 
    // ejecución del nuevo thread
    void run() override;
    // Método que se hereda de thread, el cual se emplea para indicarle 
    // al thread que debe detener su ejecución ordenadamente
    void stop() override;
};

#endif // SERVER_H
