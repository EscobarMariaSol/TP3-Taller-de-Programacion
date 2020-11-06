#ifndef FORBIDDEN_H
#define FORBIDDEN_H

#include "response.h"

class Forbidden: public Response {
public:
    Forbidden();
    ~Forbidden();
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // FORBIDDEN_H
