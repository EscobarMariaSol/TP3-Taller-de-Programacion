#ifndef SERVER_H
#define SERVER_H

#include "../common_src/socket.h"
#include "../common_src/io_handler.h"
#include "thread.h"
#include "thread_client.h"
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
// keep_running, un booleano que indica si el server debe seguir su ejecución o 
// detenerse y liberar los recursos utilizados, ordenadamente
class Server: public Thread {
private:
    Socket socket;
    Resourcer& resourcer;
    std::atomic<bool> keep_running;
    // Método que agrega clientes a la lista de clientes conectados
    // Pre: recibe la lista de clientes
    // Pos: los clientes que se conectan se agregan a la lista de clientes
    void addClients(std::list<ThreadClient*>& clients);
    // Método que se encarga de recorrer la lista de clientes conectados,
    // detectar a los que funalizaron su ejecución y eliminarlos
    // Pre: recibe una lista de los clientes despachados
    // Pos: los clientes que hayan finalizado se liberan y su lugar
    // queda invalidado
    void cleanClients(std::list<ThreadClient*>& clients);
    // Método que cierra todas las conecciones con los clientes
    // informandoles que deben detener su ejecución y luego liberando
    // los recursos utilizados
    // Pre: recibe una lista de clientes
    // Pos: los clientes han sido detenidos y los recursos utilizados
    // se han liberado
    void stopAndCleanClients(std::list<ThreadClient*>& clients);

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
