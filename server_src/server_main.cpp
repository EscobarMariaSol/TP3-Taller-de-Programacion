#include "server_program.h"

// Programa principal que lanza la ejeción del servidor
// Pre: recibe el puerto y la ruta del archivo root del
// servidor
// Pos: el programa ha sido ejecutado
int main(int argc, char *argv[]){
    if (argc == 3) {    
        ServerProgram server;
        server.startRunning(argv[1], std::string(argv[2]));
    }
    return 0;
}