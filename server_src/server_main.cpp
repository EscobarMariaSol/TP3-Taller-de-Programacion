#include "server.h"

int main(int argc, char *argv[]){
    Server server(argv[1], std::string(argv[2]));
    server.run();

    return 0;
}