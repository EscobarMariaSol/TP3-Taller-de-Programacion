#ifndef SERVER_H
#define SERVER_H

#include "../common_src/socket.h"
#include "../common_src/response.h"
#include "../common_src/io_handler.h"
#include "../common_src/thread.h"
#include "protocol.h"
#include "resourcer.h"
#include <mutex>
#include <thread>

class Server: public Thread {
private:
    std::mutex mutex;
    Socket socket;
    Resourcer resourcer;
    IOHandler io_handler;
    void saveRoot();
    void recvRequest(Socket& peer, std::stringbuf& request);
    void sendResponse(Socket& peer, const Response *response);

public:
    Server(const char *port, Resourcer& resourcer);
    ~Server();
    void run();
};

#endif // SERVER_H