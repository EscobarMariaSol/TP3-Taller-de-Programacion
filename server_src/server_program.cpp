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
    std::stringbuf exit;
    while (exit.str() != "q") {
        server->start();
        server->join();
        io_handler.getInput(exit);
    }
    delete server;
}