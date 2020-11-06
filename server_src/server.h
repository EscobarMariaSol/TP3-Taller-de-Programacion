#ifndef SERVER_H
#define SERVER_H

#include "../common_src/socket.h"
#include "resourcer.h"
#include "../common_src/response.h"
#include "../common_src/io_handler.h"
#include "protocol.h"
#include <mutex>

class Server {
private:
    std::mutex mutex;
    Socket socket;
    Resourcer resourcer;
    IOHandler io_handler;
    void saveRoot();
    void recvRequest(Socket& peer, std::stringbuf& request);
    void sendResponse(Socket& peer, const Response *response);

public:
    Server(const char *port, const std::string path);
    ~Server();
    void run();
};

#endif // SERVER_H