#ifndef FORBIDDEN_H
#define FORBIDDEN_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Forbbiden del protocolo http
class Forbidden: public Response {
public:
    // Constructor
    Forbidden();
    // Destructor
    ~Forbidden();
    // Método heredado de la clase Response
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // FORBIDDEN_H
