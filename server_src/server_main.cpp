#include "server_program.h"

// Programa principal que lanza la ejeción del servidor
// Pre: recibe el puerto y la ruta del archivo root del
// servidor
// Pos: el programa se ejecuta y devuelve 0 en cualquier caso,
// si se detecta un error durante la ejecución se imprimirá un mensaje
// que informe al respecto
int main(int argc, char *argv[]){
    if (argc == 3) {    
        ServerProgram server;
        try {
           server.startRunning(argv[1], std::string(argv[2]));
        } catch(const std::exception& e) {
            syslog(LOG_CRIT, "Error: %s", e.what());
        }
    }
    return 0;
}
