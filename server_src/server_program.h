#ifndef SERVER_PROGRAM_H
#define SERVER_PROGRAM_H

#include "resourcer.h"
#include "server.h"

class ServerProgram {
private:
    Resourcer resourcer;
    void saveRoot(IOHandler& io_handler);
    
public:
    ServerProgram();
    ~ServerProgram();
    void startRunning(const char *port, const std::string path);
};

#endif // SERVER_PROGRAM_H
