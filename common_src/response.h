#ifndef RESPONSE_H
#define RESPONSE_H

#include <sstream>
#include <string>
#include <utility>

// Clase Abstracta correspondiente a la clase respuesta del 
// protocolo http.
class Response {
public:
    Response();
    virtual ~Response();
    virtual void getResponse(std::stringbuf& str_serialize) = 0;
};

#endif // RESPONSE_H
