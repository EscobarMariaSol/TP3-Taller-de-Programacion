#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// clase correspondiente a la respuesta Not found
class NotFound: public Response {
public:
    NotFound();
    ~NotFound();
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // NOT_FOUND_H
