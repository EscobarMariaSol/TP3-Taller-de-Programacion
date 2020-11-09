#ifndef FORBIDDEN_H
#define FORBIDDEN_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Forbbiden
class Forbidden: public Response {
public:
    Forbidden();
    ~Forbidden();
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // FORBIDDEN_H
