#include "client.h"

int main(int argc, char *argv[]){
    try {
        Client client(argv[1], argv[2]);
        client.run();
    } catch(const std::exception& e) {
            std::cout << "Error: "<< e.what() << "\n";
    }
    return 0;
}
