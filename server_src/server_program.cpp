#include "server_program.h"

/************************** Métodos privados de ServerProgram ****************/

void ServerProgram::saveRoot(IOHandler& io_handler) {
    std::stringbuf root;
    io_handler.getInput(root);
    this->resourcer.addResource("/", root.str());
}

void ServerProgram::stopServer(Server& server) {
    server.stop();
    server.join();
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
    Server server(port, this->resourcer);
    try {
        char quit = 0;
        server.start();
        while (quit != 'q') {
            io_handler.getChar(quit);
        }
        stopServer(server);
    } catch(const std::exception& e) {
        stopServer(server);
        syslog(LOG_CRIT, "Error: %s", e.what());
    } catch (...) {
            syslog(LOG_CRIT, "Unknown Error\n");
    }
}
