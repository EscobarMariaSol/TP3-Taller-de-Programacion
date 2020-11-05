#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "response.h"

class NotFound: public Response {
public:
    NotFound();
    ~NotFound();
    std::pair<std::string, std::string> getResponse() override;
};

#endif // NOT_FOUND_H
