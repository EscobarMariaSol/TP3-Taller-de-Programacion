#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include "thread.h"
#include "../common_src/socket.h"
#include "protocol.h"
#include "resourcer.h"
#include "../common_src/response.h"
#include <atomic>

class ThreadClient: public Thread {
private:
    Socket peer;
    Resourcer resourcer;
    std::atomic<bool> running;
    void recvRequest(Socket& peer, std::stringbuf& request);
    void sendResponse(Socket& peer, const Response *response);

public:
    ThreadClient(Socket& peer, Resourcer& resourcer);
    ~ThreadClient();
    void run();
};

#endif // THREAD_CLIENT_H
