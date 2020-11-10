#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/socket.h"
#include "../common_src/io_handler.h"
#include <syslog.h>

// Clase correspondiente a un cliente, recibe un host y un puerto
// correspondiente a los datos del servidor al que quiere conectarse
// La clase cuenta con los siguientes atributos:
// socket, corresponde al socket a través del cual se establecerá la
// conexión con el servidor
// handler, corresponde al handler encargado de manejar la entrada
// y salida de datos por entrada o salida estándar
class Client {
private:
    Socket socket;
    IOHandler handler;
    // Método que envia un petitorio al servidor
    // Pre: recibe un buffer que almacena el petitorio
    // Pos: el petitorio ha sido enviado, en caso de ocurrir un error 
    // al enviar el mensaje se lanza una excepción informando del mismo.
    void sendRequest(const std::stringbuf& buffer);
    // Método que recibe una respuesta desde el servidor
    // Pre: recibe un buffer en el cual almacenar la respuesta
    // Pos: la respuesta ha sido recibida y almacenada, en caso de algún error
    // al recibir el mensaje, se lanzará una excepción para informar del mismo
    void recvResponse(std::stringbuf& buffer);
    
public:
    // Constructor
    Client(const char* host, const char* port);
    // Destructor
    ~Client();
    // Método encargado de lanzar la ejecución de toda la lógica del cliente
    // Pos: el cliente ha sido ejecutado, en caso de que se haya dado algún 
    // error de ejecución se mostrará un mensaje por salida estándar. 
    void run();
};

#endif // CLIENT_H
