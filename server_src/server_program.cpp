#include "server_program.h"

void ServerProgram::saveRoot(IOHandler& io_handler) {
    std::stringbuf root;
    io_handler.getInput(root);
    this->resourcer.addResource("/", root.str());
}

ServerProgram::ServerProgram(): resourcer() {
}

ServerProgram::~ServerProgram()
{
}

void ServerProgram::startRunning(const char *port, const std::string path) {
    IOHandler io_handler(path);
    saveRoot(io_handler);
    Server *server = new Server(port, std::ref(this->resourcer));
    char quit;
    server->start();
    while (quit != 'q') {
        io_handler.getChar(quit);
    }
    server->join();
    delete server;
}