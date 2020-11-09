#ifndef ADDRINFO_H
#define ADDRINFO_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <atomic>
#include <string>
#include <exception>
#include <functional>

// Clase que se encarga de manejar todo lo relacionado con 
// las direcciones struct addrinfo
// Cuenta con los siguientes atributos:
// hints, struct addrinfo que se utiliza para llamar a getaddrinfo
// addr, arreglo struct addrinfo donde se almacenaran todas las 
// direcciones disponibles para la conección del socket
class HandlerAddrinfo {
private:
    struct addrinfo hints;
    struct addrinfo *addr;
    // Método para inicializar el atributo hints
    // Pre: recibe un flag para detectar si se trata de un cliente o servidor
    // Pos: la estructura ha sido inicializada
    void init(const int flag);

public:
    // Constructor
    explicit HandlerAddrinfo(const int flag);
    // Destructor
    ~HandlerAddrinfo();
    // Método que se encarga de llamar a get addrinfo y obtener todas las
    // direcciones disponibles para conectar un socket
    // Pre: recibe un host y port válidos
    // Pos: se han obtenido las direcciones disponibles para el socket, en caso
    // de algún error se lanza una excepción informando del mismo
    void callGetAddrinfo(const char* host, const char* port);
    // Método que se encarga de abrir un file descriptor para un socket
    // Pre: previamente se ha llamado a la función callGetAddrinfo y el 
    // atributo addr ha sido correctamente inicializado
    // Pos: devuelve el número del file descriptor asignado al socket o lanza
    // una excepción informanco en caso de que suceda un error
    int openSocket() const;
    // Método que establece que el servidor está listo para escuchar conexiones
    // recorriendo todas las direcciones disponibles hasta encontrar una que 
    // permita concretar la conexión o se terminen las direcciones
    // Pre: recibe el file descriptor asociado al servidor
    // Pos: el servidor está listo para escuchar conexiones de clientes, en 
    // caso de producirse un error lanza una excepción para informar del mismo
    void bindAddress(const int fd);
    // Método que cestablece la conexión entre el cliente y el servidor,
    // recorriendo todas las direcciones disponibles para el cliente hasta 
    // que finalmente logra conectarse o se acaben las direcciones
    // Pre: recibe el file descriptor asociado al cliente
    // Pos: el cliente está listo para comunicarse con el servidor, en 
    // caso de producirse un error lanza una excepción para informar del mismo
    void connectAddress(int& fd);
};

#endif // ADDRINFO_H
