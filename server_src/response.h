#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <functional>

class Response {
public:
    Response();
    virtual ~Response();
    virtual std::pair<std::string, std::string> getResponse() = 0;
};

#endif // RESPONSE_H
