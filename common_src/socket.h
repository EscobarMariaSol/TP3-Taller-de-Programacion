#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <atomic>
#include <string>
#include <functional>
#include "addrinfo.h"


// Clase correspondiente a un socket
// La clase cuenta con un único atributo correspondiente a su file descriptor.
class Socket {
private:
    int fd;
    // Asigna el file descriptor al socket que se le pasa por parámetro
    // utilizando la información de la dirección addrs
    // Pos: se ha asignado un file descriptor al socket, si ocurre un error 
    // durante el proceso de asignación se lanza una excepción informando 
    // lo ocurrido
    void setFileDescriptor(const HandlerAddrinfo& addrinfo);
    // Establece que el servidor está listo para escuchar conexiones
    // y la cantidad de conexiones en espera que se habilitarán
    // Pos: el servidor está listo para escuchar conecciones, si un error
    // ocurre se lanza una excepción informando del mismo
    void bindAndListen(HandlerAddrinfo& addrinfo);
    // Activa la opcion de reusar la direccion en caso de que esta
    // no este disponible por un TIME_WAIT
    // Pos: se activa la opción de reusar la dirección, si ocurre un error lanza 
    // una excepción informando de lo ocurrido.
    void activeReuseAddress();
    
public:
    // Constructor 
    Socket();
    // Constructor Client
    Socket(const char* host, const char* port);
    // Constructor Server
    explicit Socket(const char *port);
    // Destructor
    virtual ~Socket();
    // Crea el socket aceptador en representación de la conexión establecida
    // Pre: Recibe una referencia a un nuevo socket
    // que funcionará como canal de comunicación
    void accept_client(Socket& accept_socket);
    // Recive un mensaje desde otro socket y lo almacena en el buffer
    // Pre: Recibe un un buffer y la cantidad de bytes a enviar
    // Post: 
    int send_msg(const char *buffer, const size_t size);
    // Envia mensajes de un socket a otro
    // Pre: un buffer y la cantidad de bytes a recibir
    // Post: 
    int recv_msg(char *buffer, const size_t size);
    // Cierra el canal de comunicación especificado del socket
    void stopComunication(int channel);
};

#endif // COMMON_SOCKET_H
