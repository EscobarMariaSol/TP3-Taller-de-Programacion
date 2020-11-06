#ifndef NOT_ALLOWED_H
#define NOT_ALLOWED_H

#include "response.h"

class NotAllowed: public Response {
public:
    NotAllowed();
    ~NotAllowed();
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // NOT_ALLOWED_H