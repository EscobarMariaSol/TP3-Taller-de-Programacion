#ifndef ADDRINFO_H
#define ADDRINFO_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <atomic>
#include <string>
#include <exception>
#include <functional>

class Addrinfo {
private:
    struct addrinfo hints;
    struct addrinfo *addr;
    void init(const int flag);

public:
    Addrinfo(const char* host, const char* port, const int flag);
    ~Addrinfo();
    void callGetAddrinfo(const char* host, const char* port);
    int getFamily() const;
    int getType() const;
    int getProtocol() const;
    void bindAddress(const int fd);
    void connectAddress(int& fd);
};

#endif // ADDRINFO_H
