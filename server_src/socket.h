#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <atomic>
#include <string>
#include <functional>


// Clase correspondiente a un socket
// La clase cuenta con un único atributo correspondiente a su file descriptor.
class Socket {
protected:
    int fd;
    
public:
    // Constructor
    Socket();
    // Destructor
    virtual ~Socket();
    // Setea el valor del file descriptor asociado al socket
    // Pre: recibe un file descriptor válido
    // Pos: el file descriptor es asignado, si el valor es inválido
    // se lanza una excepción para informar al respecto.
    void setFileDescriptor(const int fd);
    // Recive un mensaje desde otro socket y lo almacena en el buffer
    // Pre: Recibe un un buffer y la cantidad de bytes a enviar
    // Post: devuleve -1 en caso de error o 0 en caso de éxito
    int send_msg(const unsigned char *buffer, const size_t size);
    // Envia mensajes de un socket a otro
    // Pre: un buffer y la cantidad de bytes a recibir
    // Post: devuleve -1 en caso de error o 0 en caso de éxito
    int recv_msg(unsigned char *buffer, const size_t size);
};

#endif // COMMON_SOCKET_H
