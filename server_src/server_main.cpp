#include "server_program.h"

int main(int argc, char *argv[]){
    ServerProgram server;
    server.startRunning(argv[1], std::string(argv[2]));

    return 0;
}