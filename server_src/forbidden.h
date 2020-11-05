#ifndef FORBIDDEN_H
#define FORBIDDEN_H

#include "response.h"

class Forbidden: public Response {
public:
    Forbidden();
    ~Forbidden();
    std::pair<std::string, std::string> getResponse() override;
};

#endif // FORBIDDEN_H
