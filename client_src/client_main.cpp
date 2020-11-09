#include "client.h"

// Main que crea un cliente y le indica que comience
// su ejecución
// Pre: recibe un host y un puerto por parámetro
// Pos: el cliente ha sido ejecutado. Devuelve 0 para cualquier caso
// ya sea error o correcta ejecución completa
int main(int argc, char *argv[]){
    Client client(argv[1], argv[2]);
    client.run();
    return 0;
}
