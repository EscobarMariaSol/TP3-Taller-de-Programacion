#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/socket.h"
#include "../common_src/io_handler.h"
#include "../common_src/response.h"

class Client {
private:
    Socket socket;
    IOHandler handler;
    void sendRequest(const std::stringbuf& buffer);
    void recvResponse(std::stringbuf& buffer);
    
public:
    Client(const char* host, const char* port);
    ~Client();
    void run();
};

#endif // CLIENT_H
