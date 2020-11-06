#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "response.h"

class NotFound: public Response {
public:
    NotFound();
    ~NotFound();
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // NOT_FOUND_H
