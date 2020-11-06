#include "client.h"

int main(int argc, char *argv[]){
    Client client(argv[1], argv[2]);
    client.run();

    return 0;
}