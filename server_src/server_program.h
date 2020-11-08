#ifndef SERVER_PROGRAM_H
#define SERVER_PROGRAM_H

#include "resourcer.h"
#include "server.h"
#include <iostream>
#include <atomic>

// Clase correspondiente al Server principal
// Cuenta con un único atributo correspondiente al repositorio
// compartido ene el cual se guardan los recursos creados/accedidos por 
// los clientes
class ServerProgram {
private:
    Resourcer resourcer;
    // Método que se encarga de guardar en el repositorio el recurso
    // principal del servidor, correspondiente al archivo que se le
    // pasa por parámetro al iniciar el programa.
    // Pre: recibe un io_handler correctamente inicializado
    // Pos: el contenido del archivo ha sido guardado
    void saveRoot(IOHandler& io_handler);
    
public:
    // Constructor
    ServerProgram();
    // Destructor
    ~ServerProgram();
    // Método que lanza se encarga de lanzar 
    // la ejecución del thread servidor y de esperar hasta que el usuario
    // decida detener la ejecución del programa
    // Pre: recibe un puerto y ruta de archivos válidos
    // Pos: el servidor ha iniciado su ejecución
    void startRunning(const char *port, const std::string path);
};

#endif // SERVER_PROGRAM_H
