#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Not found del protocolo http
class NotFound: public Response {
public:
    // Constructor
    NotFound();
    // Destructor
    ~NotFound();
    // Método heredado de la clase Response
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // NOT_FOUND_H
