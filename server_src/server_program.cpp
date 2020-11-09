#include "server_program.h"

/************************** Métodos privados de ServerProgram ****************/

void ServerProgram::saveRoot(IOHandler& io_handler) {
    std::stringbuf root;
    io_handler.getInput(root);
    this->resourcer.addResource("/", root.str());
}

/************************** Métodos públicos de ServerProgram ****************/

ServerProgram::ServerProgram(): resourcer() {
}

ServerProgram::~ServerProgram()
{
}

void ServerProgram::startRunning(const char *port, const std::string& path) {
    IOHandler io_handler(path);
    saveRoot(io_handler);
    Server *server = new Server(port, std::ref(this->resourcer));
    char quit = 0;
    server->start();
    while (quit != 'q') {
        io_handler.getChar(quit);
    }
    server->stop();
    server->join();
    delete server;
}
