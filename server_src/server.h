#ifndef SERVER_H
#define SERVER_H

#include "server_socket.h"
#include "resourcer.h"
#include "response.h"
#include <mutex>

class Server {
private:
    std::mutex mutex;
    Resourcer resourcer;
    void saveRoot(const char *path);

public:
    Server(/* args */);
    ~Server();
    void run(const char *port, const char *path);
};

#endif // SERVER_H